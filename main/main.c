#include <stdio.h>
#include <esp_http_client.h>
#include <task.h>
#include <wifi.h>
#include <http_client.h>

void app_main() {

    for (int i = 2; i >= 0; i--) {
        printf("Starting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    wifi_start();

    get_btc_price();

    for (int i = 2; i >= 0; i--) {
        printf("Ending in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}