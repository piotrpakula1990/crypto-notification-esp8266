#include <stdio.h>
#include <esp_http_client.h>
#include <task.h>
#include <wifi.h>
#include <http_client.h>
#include <esp_log.h>
#include <math.h>
#include <gpio_manager.h>
#include <data.h>

static const char *TAG = "MAIN";

char *double_to_string(double val, signed char width, unsigned char prec, char *sout) {
    uint32_t iPart = (uint32_t) val;
    uint32_t dPart = (uint32_t) ((val - (double) iPart) * pow(10, prec));

    sprintf(sout, "%d.%d", iPart, dPart);
    return sout;
}

_Noreturn void app_main() {
    char btc_str_value[10];

    gpio_start();
    wifi_start();

    while (1) {
        char is_notification = 0;

        add_btc_price(get_btc_price());
        double *btc_table = get_last_btc_prices();

        ESP_LOGI(TAG, "btc_table[0] = %s", double_to_string(btc_table[0], 10, 4, btc_str_value));

        for (int i = 1; i < BTC_TABLE_SIZE; ++i) {

            ESP_LOGI(TAG, "btc_table[%i] = %s", i, double_to_string(btc_table[i], 10, 4, btc_str_value));

            if (btc_table[i] > 0 && btc_table[i - 1] > 0) {
                double one_percent_value;
                one_percent_value = btc_table[i] / 100;

                if (btc_table[i] > btc_table[i - 1]) {
                    if ((btc_table[i] - btc_table[i - 1]) > one_percent_value) {
                        is_notification = 1;
                    }
                } else {
                    if ((btc_table[i - 1] - btc_table[i]) > one_percent_value) {
                        is_notification = 1;
                    }
                }
            }
        }

        if (is_notification == 1) {
            ESP_LOGI(TAG, "RED-LED ON");
            set_red_led_on();
        } else {
            ESP_LOGI(TAG, "RED-LED OFF");
            set_red_led_off();
        }

        vTaskDelay(120000 / portTICK_RATE_MS); // ~120s
    }
}