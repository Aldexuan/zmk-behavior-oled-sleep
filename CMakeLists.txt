# SPDX-License-Identifier: MIT
target_sources_ifdef(CONFIG_ZMK_BEHAVIOR_OLED_SLEEP app PRIVATE src/behaviors/oled_sleep.c)
zephyr_include_directories(${APPLICATION_SOURCE_DIR}/include)
zephyr_include_directories(${APPLICATION_SOURCE_DIR}/src/behaviors)
