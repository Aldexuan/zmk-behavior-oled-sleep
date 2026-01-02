/*
 * Copyright (c) 2026 Aldexuan
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/display.h>
#include <zmk/behavior.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static bool oled_is_awake = true;
static const struct device *display_dev;

static int oled_sleep_binding_accept(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    if (!device_is_ready(display_dev)) {
        LOG_WRN("OLED display not ready");
        return -ENODEV;
    }

    if (oled_is_awake) {
        display_blanking_on(display_dev);
        LOG_INF("OLED -> sleep");
    } else {
        display_blanking_off(display_dev);
        LOG_INF("OLED -> awake");
    }

    oled_is_awake = !oled_is_awake;
    return 0;
}

static const struct zmk_behavior_driver_api oled_sleep_behavior_driver_api = {
    .accept = oled_sleep_binding_accept,
};

ZMK_BEHAVIOR_DECLARE(oled_sleep, oled_sleep_behavior_driver_api);
ZMK_BEHAVIOR_DEFINE(oled_sleep, DT_DRV_INST(0));

static int oled_sleep_behavior_init(const struct device *dev) {
    ARG_UNUSED(dev);
    display_dev = DEVICE_DT_GET(DT_CHOSEN(zmk_display));
    if (!device_is_ready(display_dev)) {  // 更严谨：先 get 再 check ready
        LOG_ERR("Failed to get or initialize ZMK display device");
        return -ENODEV;
    }
    LOG_INF("OLED sleep behavior initialized");
    return 0;
}

SYS_INIT(oled_sleep_behavior_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);