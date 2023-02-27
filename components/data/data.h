#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define BTC_TABLE_SIZE 5

double *get_last_btc_prices();

void add_btc_price(struct price p);

#ifdef __cplusplus
}
#endif