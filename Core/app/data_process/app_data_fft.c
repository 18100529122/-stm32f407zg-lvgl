#include "app_data_fft.h"
#include "arm_math.h"
#include <string.h>
#include <stdio.h>

fft_result_t g_fft_result;

/* 定义外部 SRAM 地址 (避开 LVGL 显存、内存池以及 ADC 缓冲区) */
#define FFT_SRAM_ADDR_BASE  0x68082000
#define FFT_INPUT_ADDR      (FFT_SRAM_ADDR_BASE)
#define FFT_OUTPUT_ADDR     (FFT_INPUT_ADDR + FFT_LENGTH * 4)

/* 实例结构体放回内部 SRAM，确保稳定性 */
static arm_rfft_fast_instance_f32 fft_instance;
/* 计算大缓存留在外部 SRAM */
static float32_t *fft_input_buf = (float32_t *)FFT_INPUT_ADDR;
static float32_t *fft_output_buf = (float32_t *)FFT_OUTPUT_ADDR;

/**
 * @brief 使用 arm_math 库进行实数 FFT 计算
 */
void app_data_fft_compute(uint16_t *input_data, uint32_t length) {
    if (length > FFT_LENGTH) length = FFT_LENGTH;

    /* 1. 数据预处理 */
    for (uint32_t i = 0; i < length; i++) {
        fft_input_buf[i] = (float32_t)input_data[i];
    }
    /* 如果输入长度不足，补零 */
    for (uint32_t i = length; i < FFT_LENGTH; i++) {
        fft_input_buf[i] = 0.0f;
    }

    /* 2. 动态计算并去除直流分量 (减去平均值) */
    float32_t meanVal;
    arm_mean_f32(fft_input_buf, length, &meanVal);
    arm_offset_f32(fft_input_buf, -meanVal, fft_input_buf, length);

    /* 3. 执行实数 FFT */
    arm_rfft_fast_f32(&fft_instance, fft_input_buf, fft_output_buf, 0);

    /* 4. 计算复数幅值 */
    /* 我们只需要计算前 N/2 个点的幅值 */
    /* 注意：arm_cmplx_mag_f32 会将 [R, I] 对转换为幅值 */
    /* 由于 rfft_fast 的特殊输出格式，我们从第 1 个有效复数对开始计算，避开 DC/Nyquist 的 mag[0] 混淆 */
    
    // 先计算所有点的幅值
    arm_cmplx_mag_f32(fft_output_buf, g_fft_result.magnitudes, FFT_LENGTH / 2);
    
    /* 修正幅值数组：
     * 原始 arm_cmplx_mag_f32 计算出的 mag[0] 是 sqrt(R[0]^2 + R[N/2]^2)，这是无效的。
     * 正确的 mag[0] 应该是 |R[0]| (DC)。
     * 正确的频率 Bin 从 mag[1] 开始。
     */
    g_fft_result.magnitudes[0] = fabsf(fft_output_buf[0]) * (1.0f / FFT_LENGTH); // 真正的 DC
    
    /* 5. 归一化处理 */
    /* 对于 i > 0 的频率点，幅值需要乘以 2/N */
    float32_t scale = 2.0f / FFT_LENGTH;
    for (uint32_t i = 1; i < FFT_LENGTH / 2; i++) {
        g_fft_result.magnitudes[i] = g_fft_result.magnitudes[i] * scale;
    }
    
    /* 强制将 DC 设为 0 以便观察交流分量 */
    g_fft_result.magnitudes[0] = 0.0f;

    /* 6. 提取 50Hz - 500Hz 频率分量 (Fs = 5000Hz, N = 512, Bin_Res = 9.765Hz) */
    float32_t fs = 5000.0f;
    float32_t bin_res = fs / FFT_LENGTH;
    for (int i = 0; i < FREQ_COMP_NUM; i++) {
        float32_t target_freq = 50.0f * (i + 1);
        /* 使用四舍五入寻找最接近的 Bin */
        int bin_idx = (int)(target_freq / bin_res + 0.5f);
        if (bin_idx < FFT_LENGTH / 2) {
            g_fft_result.freq_values[i] = g_fft_result.magnitudes[bin_idx];
        }
    }
}

void app_data_fft_init(void) {
    memset(&g_fft_result, 0, sizeof(fft_result_t));
    /* 初始化 CMSIS-DSP 实数 FFT 实例 */
    arm_rfft_fast_init_f32(&fft_instance, FFT_LENGTH);
}
