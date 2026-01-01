/*
 * Copyright (c) 2026 Aldexuan
 * SPDX-License-Identifier: MIT
 */

#include <zmk/behavior.h>
#include <drivers/display.h>

static int oled_sleep_binding_accept(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    const struct device *display = DEVICE_DT_GET(DT_CHOSEN(zmk_display));
    if (!device_is_ready(display)) {
        return -ENODEV;
    }
    static bool is_on = true;
    display_blanking_off(display);
    if (!is_on) {
        display_blanking_off(display);
    } else {
        display_blanking_on(display);
    }
    is_on = !is_on;
    return ZMK_BEHAVIOR_ACCEPTED;
}

static const struct zmk_behavior_driver_api oled_sleep_behavior_driver_api = {
    .binding_accept = oled_sleep_binding_accept,
};

ZMK_BEHAVIOR_DECLARE(oled_sleep, "zmk,behavior-oled-sleep",
                     &oled_sleep_behavior_driver_api);