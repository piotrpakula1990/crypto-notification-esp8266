#include <esp_log.h>
#include <esp_err.h>
#include <esp_http_client.h>
#include "http_client.h"

/* SDK Config
 * CONFIG_ESP_TLS_INSECURE=y
 * CONFIG_ESP_TLS_SKIP_SERVER_CERT_VERIFY=y
 * CONFIG_HTTP_BUF_SIZE=512
 * */

/* Buffer for ESP8266 must be set to ~512b, cause low memory problem. */
#define MAX_HTTP_OUTPUT_BUFFER 512

static const char *TAG = "HTTP_CLIENT";

void get_btc_price() {

    char output_buffer[MAX_HTTP_OUTPUT_BUFFER] = {0};

    esp_http_client_config_t config = {
            .url = "https://api.coinbase.com/v2/prices/BTC-USD/buy",
            .method  = HTTP_METHOD_GET
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);

    esp_err_t err = esp_http_client_open(client, 0);

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP GET OK");
        int content_length = esp_http_client_fetch_headers(client);
        if (content_length >= 0) {
            int data_read = esp_http_client_read_response(client, output_buffer, MAX_HTTP_OUTPUT_BUFFER);
            if (data_read >= 0) {
                ESP_LOGI(TAG, "HTTP GET %d, response = %s", esp_http_client_get_status_code(client), output_buffer);
                ESP_LOG_BUFFER_HEX(TAG, output_buffer, strlen(output_buffer));
            } else {
                ESP_LOGE(TAG, "Failed to read response");
            }
        } else {
            ESP_LOGE(TAG, "HTTP client fetch headers failed");
        }
    } else {
        ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(err));
    }

    esp_http_client_close(client);
}