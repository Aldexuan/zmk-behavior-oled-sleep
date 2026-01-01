# SPDX-License-Identifier: MIT
zephyr_library_sources_ifdef(CONFIG_ZMK_BEHAVIOR_OLED_SLEEP src/behavior/oled_sleep.c)
zephyr_include_directories(${APPLICATION_SOURCE_DIR}/include)
zephyr_include_directories(${APPLICATION_SOURCE_DIR}/src/behaviors)