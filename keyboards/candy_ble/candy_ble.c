#include "candy_ble.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_power.h"
#include "nrfx_power.h"
#include "nrf.h"
#include "app_ble_func.h"
#undef PACKED



#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// adafruit bootloader, send "dfu" to debug serial port
#define DFU_MAGIC_UF2_RESET             0x57
void bootloader_jump(void) {
  sd_power_gpregret_set(0, DFU_MAGIC_UF2_RESET);
  NVIC_SystemReset();
}

static bool ble_flag = false;

void nrfmicro_power_enable(bool enable) {
	// if(nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_CONNECTED
 //    || nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_READY){
	// 	enable=true;
	// }
	if (enable) {
			
		nrf_gpio_cfg_output(POWER_PIN);	//disable power pin feature
		nrf_gpio_pin_set(POWER_PIN);
		
	} else {
		
		nrf_gpio_cfg_output(POWER_PIN); //disable power pin feature
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

//switch to usb mode when usb cable connected
void check_usb_power()
{
	if (nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_CONNECTED ||
    	nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_READY) {
		if(!get_usb_enabled() && get_ble_enabled())
		{
    		set_usb_enabled(true);
			set_ble_enabled(false);
		}
  	} else {
  		if(get_usb_enabled() && !get_ble_enabled())
		{
    		set_usb_enabled(false);
			set_ble_enabled(true);
		}
  	}
}

void eeprom_update(void);

void nrfmicro_init() {
  // configure pins
  nrf_gpio_cfg_output(POWER_PIN);
  nrf_gpio_cfg_output(LED_PIN);
  nrf_gpio_cfg_input(SWITCH_PIN, NRF_GPIO_PIN_PULLDOWN);

  nrf_gpio_cfg_input(PIN12, NRF_GPIO_PIN_PULLDOWN);	//detect charging pin

  nrf_delay_ms(100);

  // eeconfig_read_rgblight();



  check_ble_switch(true);

  // nrf_gpio_cfg_output(PIN12);
  // nrf_gpio_pin_set(PIN12);
  // nrf_delay_ms(5000);
  // nrf_gpio_pin_clear(PIN12);
  // eeconfig_update_rgblight_default();
  // rgblight_enable();
	// eeprom_update(); 
  // eeconfig_read_rgblight();
	// rgblight_disable();
   // nrfmicro_power_enable(false); //power pin
  // if(!rgblight_config.enable)
  // {
  // 	nrfmicro_power_enable(false); //power pin
  // }

  // if(rgblight_config.enable)
  // {
  // 	nrfmicro_power_enable(true); //power pin
  // }
}

void update_caps_led()
{
	// uint8_t leds = host_keyboard_leds();
	// leds & (1 << USB_LED_CAPS_LOCK)?nrf_gpio_pin_set(LED_PIN):nrf_gpio_pin_clear(LED_PIN);
	// nrf_gpio_pin_set(LED_PIN);
	// uint8_t led_usb_state = host_keyboard_leds();
	// led_usb_state & (1 << USB_LED_CAPS_LOCK) ? nrf_gpio_pin_set(LED_PIN):nrf_gpio_pin_clear(LED_PIN);
	// nrf_gpio_pin_write(LED_PIN,led_usb_state & (1 << USB_LED_CAPS_LOCK));

	if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)){
		nrf_gpio_pin_set(LED_PIN);
	} else {
		nrf_gpio_pin_clear(LED_PIN);
	}

}

void nrfmicro_update() {
  // check_ble_switch(false);
  check_usb_power();
  eeprom_update(); 
  // update_caps_led();
}

/*
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        // writePin sets the pin high for 1 and low for 0.
        // In this example the pins are inverted, setting
        // it low/0 turns it on, and high/1 turns the LED off.
        // This behavior depends on whether the LED is between the pin
        // and VCC or the pin and GND.
        // writePin(B1, !led_state.caps_lock);
        
    }
    return res;
}
*/

void keyboard_post_init_kb()
{
	nrfmicro_power_enable(false); //power pin
  // if(!rgblight_config.enable)
  // {
  // 	nrfmicro_power_enable(false); //power pin
  // }
  if(rgblight_config.enable)
  {
  	nrfmicro_power_enable(true); //power pin
  }
  // {
  // 	nrfmicro_power_enable(true); //power pin
  // }
}





