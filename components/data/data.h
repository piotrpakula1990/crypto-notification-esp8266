#pragma once

#ifdef __cplusplus
extern "C" {
#endif

double *get_last_btc_prices();

void add_btc_price(struct price p);

#ifdef __cplusplus
}
#endif