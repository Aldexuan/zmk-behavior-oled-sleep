/*
 * Copyright (c) 2026 Aldexuan
 * SPDX-License-Identifier: MIT
 */

#include <zmk/behavior.h>
#include <drivers/oled.h>

static bool oled_sleep_state = false;

static int oled_sleep_binding_accept(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    oled_set_display(!oled_sleep_state);
    oled_sleep_state = !oled_sleep_state;
    return ZMK_BEHAVIOR_ACCEPTED;
}

static const struct zmk_behavior_driver_api oled_sleep_behavior_driver_api = {
    .binding_accept = oled_sleep_binding_accept,
};

ZMK_BEHAVIOR_DECLARE(oled_sleep_behavior, "zmk,behavior-oled-sleep",
                     &oled_sleep_behavior_driver_api);