#include "bsp_time.h"
#include "tim.h"  // 包含CubeMX生成的tim.h，其中包含了htim5句柄的声明

// 声明 CubeMX 生成的 TIM5 句柄
extern TIM_HandleTypeDef htim5;

/**
 * @brief 定时器初始化函数
 * @note 封装CubeMX生成的TIM5初始化，并启动定时器
 */
void bsp_time_init(void)
{
	HAL_TIM_Base_Start(&htim5);	 // 启动TIM5定时器
}

/**
 * @brief 获取当前微秒时间戳
 * @return uint32_t 当前微秒数
 */
uint32_t bsp_time_get_us(void)
{
	return __HAL_TIM_GET_COUNTER(&htim5);
}