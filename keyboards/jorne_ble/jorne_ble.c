#include "jorne_ble.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_power.h"
#include "nrfx_power.h"
#include "nrfx_pwm.h"
#include "nrf.h"
#include "app_ble_func.h"

// adafruit bootloader, send "dfu" to debug serial port
#define DFU_MAGIC_UF2_RESET             0x57
void bootloader_jump(void) {
  sd_power_gpregret_set(0, DFU_MAGIC_UF2_RESET);
  NVIC_SystemReset();
}

static bool ble_flag = false;


extern 

void nrfmicro_power_enable(bool enable) {

  // do not switch power off if usb present
  if (nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_CONNECTED
    || nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_READY)
      enable = true;

  if (enable) {
    nrf_gpio_cfg_output(POWER_PIN);
    nrf_gpio_pin_set(POWER_PIN);
  } else {
    nrf_gpio_cfg_output(POWER_PIN);
    nrf_gpio_pin_clear(POWER_PIN); // works
    //input with pull-up consumes less than without it when pin is open (Hasu)
    //nrf_gpio_cfg_input(POWER_PIN, NRF_GPIO_PIN_PULLUP); // doesn't seem to work
    //nrf_gpio_cfg_input(POWER_PIN, NRF_GPIO_PIN_NOPULL); // neither this
    //nrf_gpio_cfg_input(POWER_PIN, NRF_GPIO_PIN_PULLDOWN); // or this
  }
}

void check_ble_switch(bool init) {
  uint8_t value = nrf_gpio_pin_read(SWITCH_PIN);

  if (init || ble_flag != value) {
    ble_flag = value;

    // mind that it doesn't disable BLE completely, it only disables send
    set_usb_enabled(!ble_flag);
    set_ble_enabled(ble_flag);

    nrf_gpio_pin_clear(LED_PIN);

    if (ble_flag) {
      // blink twice on ble enabled
      for (int i=0; i<2; i++) {
        nrf_gpio_pin_set(LED_PIN);
        nrf_delay_ms(100);
        nrf_gpio_pin_clear(LED_PIN);
        nrf_delay_ms(100);
      }
    }
  }
}

#define RGBLIGHT_MODE_BREATHING 15

#ifdef RGBLIGHT_ENABLE
extern int RGB_current_mode;
extern rgblight_config_t rgblight_config;
#endif
void rgb_test() {
#ifdef RGBLIGHT_ENABLE

  //nrfmicro_power_enable(true);
  //eeconfig_update_rgblight_default();

  //rgblight_mode_noeeprom(15); //hangs!

  //rgblight_enable();

  //rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  //rgblight_sethsv_noeeprom(180, 255, 255); // sets the color to teal/cyan without saving
  //rgblight_mode_noeeprom(3); // sets mode to Fast breathing without savin

/*
  eeconfig_update_rgblight_default();

  //rgblight_mode(15); //turns rgb off
  //rgblight_mode_noeeprom(15); // turns rgb off

  for (int i=0; i<2; i++) {
    rgblight_enable();
    nrf_delay_ms(250);
    rgblight_disable();
    nrf_delay_ms(250);
  }

  rgblight_enable();
*/
#endif
}

void nrfmicro_init() {
  // configure pins
  nrf_gpio_cfg_output(POWER_PIN);
  nrf_gpio_cfg_output(LED_PIN);
  nrf_gpio_cfg_input(SWITCH_PIN, NRF_GPIO_PIN_PULLDOWN);

  nrfmicro_power_enable(true);

  nrf_delay_ms(100);
  //nrfmicro_power_enable(false);

  check_ble_switch(true);

  nrf_delay_ms(100);

  eeconfig_update_rgblight_default();
  //rgblight_mode_noeeprom(15); //hangs!
  nrf_delay_ms(250);
  rgblight_toggle();

  //rgb_test();
}

void nrfmicro_update() {
  check_ble_switch(false);
}

