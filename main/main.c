#include <stdio.h>
#include <esp_http_client.h>
#include <task.h>
#include <wifi.h>
#include <http_client.h>
#include <esp_log.h>
#include <math.h>
#include "data.h"

char *double_to_string(double val, signed char width, unsigned char prec, char *sout) {
    uint32_t iPart = (uint32_t) val;
    uint32_t dPart = (uint32_t) ((val - (double) iPart) * pow(10, prec));

    sprintf(sout, "%d.%d", iPart, dPart);
    return sout;
}

void app_main() {

    for (int i = 2; i >= 0; i--) {
        printf("Starting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    wifi_start();

    struct price btc = get_btc_price();

    char btc_value[10];
    double_to_string(btc.value, 10, 4, btc_value);
    printf("Return: crypto: %s, price = %s\n", btc.crypto, btc_value);

    for (int i = 2; i >= 0; i--) {
        printf("Ending in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}