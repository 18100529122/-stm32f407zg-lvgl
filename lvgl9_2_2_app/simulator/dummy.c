#include "comm.h"
#include "lvgl.h"
#include <stdio.h>
#include <time.h>

#define USE_SERIAL_PORT 0

static uint32_t send_cmd_buf(uint8_t *cmd_buf, uint16_t cmd_len);

static uint32_t handle_command(uint8_t cmd, uint16_t code, uint16_t type,
                               uint16_t len, uint8_t *data);

uint32_t process_command(uint8_t cmd, uint16_t code, uint16_t type,
                         uint16_t len, uint8_t *data) {
#if USE_SERIAL_PORT
  uint16_t buf_len = 16 + len;
  uint8_t *buf = lv_mem_alloc(buf_len);
  lv_memset_00(buf, buf_len);
  uint8_t *buf_ptr = buf;
  // pack head
  buf_ptr += 4;
  // pack manufacturer_id
  lv_memcpy(buf_ptr, &(uint16_t){0}, 2);
  buf_ptr += 2;
  // pack model_id
  lv_memcpy(buf_ptr, &(uint16_t){0}, 2);
  buf_ptr += 2;
  // pack cmd
  lv_memcpy(buf_ptr, &(uint8_t){cmd}, 1);
  buf_ptr += 1;
  // pack code
  lv_memcpy(buf_ptr, &(uint16_t){code}, 2);
  buf_ptr += 2;
  // pack reserved
  buf_ptr += 1;
  // pack type
  lv_memcpy(buf_ptr, &(uint16_t){type}, 2);
  buf_ptr += 2;
  // pack len
  lv_memcpy(buf_ptr, &(uint16_t){len}, 2);
  buf_ptr += 2;

  if (len > 0) {
    // pack data
    lv_memcpy(buf_ptr, data, len);
    buf_ptr += len;
  }
  uint32_t result = send_cmd_buf(buf, buf_len);

  lv_mem_free(buf);

  return result;
#else
  return handle_command(cmd, code, type, len, data);
#endif
}

static uint32_t send_cmd_buf(uint8_t *cmd_buf, uint16_t cmd_len) {
  printf("send_cmd_buf:");
  for (uint16_t i = 0; i < cmd_len; i++) {
    printf("%02X ", cmd_buf[i]);
  }
  printf("\n");

  if (cmd_len < 16) {
    printf("Invalid command length %d\n", cmd_len);
    return 1;
  }

  uint32_t head = 0;
  uint16_t manufacture_id = 0;
  uint16_t model_id = 0;
  uint8_t cmd = 0;
  uint16_t code = 0;
  uint8_t reserved = 0;
  uint16_t type = 0; // int
  uint16_t len = 0;
  uint32_t data = 0;

  uint8_t *buf_ptr = cmd_buf;

  lv_memcpy(&head, buf_ptr, sizeof(head));
  buf_ptr += sizeof(head);
  lv_memcpy(&manufacture_id, buf_ptr, sizeof(manufacture_id));
  buf_ptr += sizeof(manufacture_id);
  lv_memcpy(&model_id, buf_ptr, sizeof(model_id));
  buf_ptr += sizeof(model_id);
  lv_memcpy(&cmd, buf_ptr, sizeof(cmd));
  buf_ptr += sizeof(cmd);
  lv_memcpy(&code, buf_ptr, sizeof(code));
  buf_ptr += sizeof(code);
  lv_memcpy(&reserved, buf_ptr, sizeof(reserved));
  buf_ptr += sizeof(reserved);
  lv_memcpy(&type, buf_ptr, sizeof(type));
  buf_ptr += sizeof(type);
  lv_memcpy(&len, buf_ptr, sizeof(len));
  buf_ptr += sizeof(len);
  lv_memcpy(&data, buf_ptr, len);
  buf_ptr += len;

  printf("send_cmd_buf: cmd=%d, code=%d, type=%d, len=%d\n", cmd, code, type,
         len);

  return 0;
}

static uint32_t handle_command(uint8_t cmd, uint16_t code, uint16_t type,
                               uint16_t len, uint8_t *data) {
  LV_LOG_USER("handle_command cmd %d code %d type %d len %d\n", cmd, code, type,
              len);
  static uint8_t bt_status = 0;
  static uint8_t wifi_status = 0;
  static uint8_t battery_status = 0;

  switch (cmd) {
  case CMD_BT: {
    switch (code) {
    case CMD_BT_STATUS: {
      LV_LOG_TRACE("cmd bt status\n");
      send_event(get_current_event_table(), EVT_BT, EVT_BT_CHANGED,
                 &(uint8_t){bt_status}, bt_status);
      break;
    }

    case CMD_BT_CONNECT: {
      LV_LOG_TRACE("cmd bt connect\n");
      if (len > 0) {
        bt_status = data[0];
        send_event(get_current_event_table(), EVT_BT, EVT_BT_CHANGED, data,
                   data[0]);
      } else {
        LV_LOG_TRACE("cmd bt connect: no data\n");
      }
      break;
    }

    default:
      LV_LOG_WARN("Invalid command code %d\n", code);
      break;
    }
    break;
  }

  case CMD_WIFI: {
    switch (code) {
    case CMD_WIFI_STATUS: {
      LV_LOG_TRACE("cmd wifi status\n");
      send_event(get_current_event_table(), EVT_WIFI, EVT_WIFI_CHANGED,
                 &(uint8_t){wifi_status}, wifi_status);
      break;
    }

    case CMD_WIFI_CONNECT: {
      LV_LOG_TRACE("cmd wifi connect\n");
      if (len > 0) {
        wifi_status = data[0];
        send_event(get_current_event_table(), EVT_WIFI, EVT_WIFI_CHANGED, data,
                   data[0]);
      } else {
        LV_LOG_TRACE("cmd wifi connect: no data\n");
      }
      break;
    }

    default:
      LV_LOG_WARN("Invalid command code %d\n", code);
      break;
    }

    break;
  }

  case CMD_BATTERY: {
    switch (code) {
    case CMD_BATTERY_STATUS: {
      LV_LOG_TRACE("cmd battery status\n");
      send_event(get_current_event_table(), EVT_BATTERY, EVT_BATTERY_CHANGED,
                 &(uint8_t){battery_status}, battery_status);
      break;
    }

    default:
      break;
    }
    break;
  }

  default: {
    LV_LOG_WARN("Invalid command %d\n", cmd);
    break;
  }
  }

  return 0;
}

void time_timer_cb(lv_timer_t *timer) {
  time_t rawtime;
  struct tm *timeinfo;
  char buffer[80];

  // 获取当前系统时间
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  // 将时间格式化为字符串
  // strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
  strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
  send_event(get_current_event_table(), EVT_TIME, EVT_TIME_CHANGED,
             (uint8_t *)buffer, 0);
}

void battery_timer_cb(lv_timer_t *timer) {
  // printf("battery_time_cb\n");
  static uint8_t battery_vol = 0;
  uint8_t curr_vol = (battery_vol++) % 3;
  send_event(get_current_event_table(), EVT_BATTERY, EVT_BATTERY_CHANGED, NULL,
             curr_vol);
}

/* 1️⃣
 * File system callbacks for LVGL
 */
static void *fs_open(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode) {
  LV_UNUSED(drv);
  const char *flags = (mode == LV_FS_MODE_WR) ? "wb" : "rb";
  return fopen(path, flags);
}

static lv_fs_res_t fs_close(lv_fs_drv_t *drv, void *file) {
  LV_UNUSED(drv);
  fclose((FILE *)file);
  return LV_FS_RES_OK;
}

static lv_fs_res_t fs_read(lv_fs_drv_t *drv, void *file, void *buf,
                           uint32_t btr, uint32_t *br) {
  LV_UNUSED(drv);
  *br = fread(buf, 1, btr, (FILE *)file);
  return (*br > 0) ? LV_FS_RES_OK : LV_FS_RES_UNKNOWN;
}

static lv_fs_res_t fs_seek(lv_fs_drv_t *drv, void *file, uint32_t pos,
                           lv_fs_whence_t whence) {
  LV_UNUSED(drv);
  int origin = (whence == LV_FS_SEEK_SET)   ? SEEK_SET
               : (whence == LV_FS_SEEK_CUR) ? SEEK_CUR
                                            : SEEK_END;
  fseek((FILE *)file, pos, origin);
  return LV_FS_RES_OK;
}

static lv_fs_res_t fs_tell(lv_fs_drv_t *drv, void *file, uint32_t *pos) {
  LV_UNUSED(drv);
  *pos = ftell((FILE *)file);
  return LV_FS_RES_OK;
}

/* 2️⃣ Register the file system */
void register_fs() {
  static lv_fs_drv_t fs_drv;
  lv_fs_drv_init(&fs_drv);
  fs_drv.letter = 'S'; // Drive letter
  fs_drv.open_cb = fs_open;
  fs_drv.close_cb = fs_close;
  fs_drv.read_cb = fs_read;
  fs_drv.seek_cb = fs_seek;
  fs_drv.tell_cb = fs_tell;
  lv_fs_drv_register(&fs_drv);
}
