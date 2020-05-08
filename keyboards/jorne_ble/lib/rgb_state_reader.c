#ifdef RGBLIGHT_ENABLE

#include QMK_KEYBOARD_H
#include <stdio.h>

extern rgblight_config_t rgblight_config;
char rbf_info_str[24];
const char *read_rgb_info(void) {

  if (rgblight_config.enable)
    snprintf(rbf_info_str, sizeof(rbf_info_str), "RGB: %-2d HSV: %02x%02x%02x",
      rgblight_config.mode, rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
  else
    snprintf(rbf_info_str, sizeof(rbf_info_str), "RGB: off");

  return rbf_info_str;
}
#endif
