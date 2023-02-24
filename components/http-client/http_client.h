#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct price {
    char *crypto;
    double value;
};

struct price get_btc_price();

#ifdef __cplusplus
}
#endif