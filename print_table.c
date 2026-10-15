#include <stdio.h>
#include "print_table.h"
#include "set_values.h"
#include "calculator.h"

void print_table(const char postfix[], const int variables[], int count)
{
    int values[26] = {0};
    for (int i = 0; i < count; ++i) {
        printf("%c ", 'A' + variables[i]);
    }
    
    printf("| F\n");

    for (int i = 0; i < count; ++i) {
        printf("--");
    }
    printf("|--\n");

    for (unsigned long row = 0; row < (1UL << count); ++row) {
        set_values(row, variables, count, values);
        for (int i = 0; i < count; ++i) {
            printf("%d ", values[variables[i]]);
        }
        printf("| %d\n", evaluate(postfix, values));
    }
    printf("\n");
}