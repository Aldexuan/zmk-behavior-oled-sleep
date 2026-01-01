# SPDX-License-Identifier: MIT

if(CONFIG_ZMK_BEHAVIOR_OLED_SLEEP)
    zmk_behavior_library(
        NAME oled_sleep
        SOURCES src/behavior/oled_sleep.c
    )
endif()