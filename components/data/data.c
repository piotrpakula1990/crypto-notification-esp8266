#include <http_client.h>
#include "data.h"

#define BTC_TABLE_SIZE 10

struct btc_data {
    char *crypto;
    int index;
    unsigned char is_full;
    double values[BTC_TABLE_SIZE];
};

static struct btc_data btc = {
        .crypto = "BTC",
        .index = 0,
        .is_full = 0
};

double *get_last_btc_prices() {
    static double buffer[BTC_TABLE_SIZE];
    int buffer_index = 0;

    for (int i = btc.index - 1; i >= 0; --i) {

        if (btc.values[i] != 0) {
            buffer[buffer_index] = btc.values[i];
            buffer_index++;
        }
    }

    if (btc.is_full == 1) {
        int count = 10 - btc.index;

        for (int i = count; i > 0; --i) {
            buffer[buffer_index] = btc.values[i + btc.index - 1];
            buffer_index++;
        }
    }

    return buffer;
}

void add_btc_price(struct price p) {
    btc.values[btc.index] = p.value;
    btc.index = btc.index + 1;

    if (btc.index == BTC_TABLE_SIZE) { // reset index
        btc.index = 0;
        btc.is_full = 1;
    }
}