#include "tools.h"
#include <math.h>
#include <stdio.h>

char *double_to_string(double val, signed char width, unsigned char prec, char *sout) {
    uint32_t iPart = (uint32_t) val;
    uint32_t dPart = (uint32_t)((val - (double) iPart) * pow(10, prec));

    sprintf(sout, "%d.%d", iPart, dPart);
    return sout;
}