#include "set_values.h"
#include <stdio.h>

void set_values(unsigned long row, const int variables[], int count, int values[])
{
    for (int i = 0; i < count; ++i) {
        values[variables[i]] = (int)((row >> (count - 1 - i)) & 1UL);
    }
}