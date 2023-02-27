#include <gpio.h>
#include "gpio_manager.h"

#define GPIO_3     3    // D0, red led

void gpio_start() {
    gpio_config_t io_conf = {
            .intr_type = GPIO_INTR_DISABLE,
            .mode = GPIO_MODE_OUTPUT,
            .pin_bit_mask =  1ULL << GPIO_3,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .pull_up_en = GPIO_PULLUP_DISABLE
    };
    gpio_config(&io_conf);
}

void set_red_led_on() {
    gpio_set_level(GPIO_3, 1);
}

void set_red_led_off() {
    gpio_set_level(GPIO_3, 0);
}