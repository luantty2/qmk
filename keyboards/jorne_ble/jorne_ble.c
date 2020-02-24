#include "jorne_ble.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_power.h"
#include "nrf.h"
#include "app_ble_func.h"

// adafruit bootloader, send "dfu" to debug serial port
#define DFU_MAGIC_UF2_RESET             0x57
void bootloader_jump(void) {
  sd_power_gpregret_set(0, DFU_MAGIC_UF2_RESET);
  NVIC_SystemReset();
}

//static bool ble_flag = false;

void check_ble_switch(bool init) {
/*
	uint8_t value = nrf_gpio_pin_read(SWITCH_PIN);
	if (ble_flag != value || init) {
		ble_flag = value;
		set_usb_enabled(!ble_flag);
		set_ble_enabled(ble_flag);
	}
*/
}

void nrfmicro_init() {

  set_usb_enabled(true);

  // power control for LEDs and OLED
  nrf_gpio_cfg_output(POWER_PIN);
  nrf_gpio_pin_set(POWER_PIN);

  // blink on power on
  nrf_gpio_cfg_output(LED_PIN);
  nrf_gpio_cfg_input(SWITCH_PIN, NRF_GPIO_PIN_PULLDOWN);

  check_ble_switch(true);

  for (int i = 0; i < 2; i++) {
    nrf_gpio_pin_set(LED_PIN);
    nrf_delay_ms(100);

    nrf_gpio_pin_clear(LED_PIN);
    nrf_delay_ms(100);
  }

  nrf_gpio_pin_clear(LED_PIN);

}

void nrfmicro_update() {
  check_ble_switch(false);
}

