/*
 * Copyright (c) 2026 Aldexuan
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/display.h>
#include <zmk/behavior.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

// 全局状态：true = 显示开启（唤醒），false = 休眠（关闭）
static bool oled_is_awake = true;

static int oled_sleep_binding_accept(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zmk_display));

    if (!device_is_ready(display_dev)) {
        LOG_WRN("OLED display not ready");
        return -ENODEV;
    }

    if (oled_is_awake) {
        // 进入休眠：开启 blanking（SSD1306 会进入低功耗）
        display_blanking_on(display_dev);
        LOG_INF("OLED -> sleep");
    } else {
        // 唤醒：关闭 blanking，恢复显示
        display_blanking_off(display_dev);
        LOG_INF("OLED -> awake");
    }

    oled_is_awake = !oled_is_awake;
    return ZMK_BEHAVIOR_ACCEPT;
}

static const struct zmk_behavior_driver_api oled_sleep_behavior_driver_api = {
    .accept = oled_sleep_binding_accept,
};

ZMK_BEHAVIOR_DECLARE(oled_sleep, oled_sleep_behavior_driver_api);
ZMK_BEHAVIOR_DEFINE(oled_sleep, DT_DRV_INST(0));