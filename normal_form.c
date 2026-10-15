#include <stdio.h>
#include "normal_form.h"
#include "make_postfix.h"
#include "set_values.h"
#include "calculator.h"

void print_normal_form(const char postfix[], const int variables[], int count, int is_dnf)
{
    int values[26]  = {0};
    int first = 1;
    printf("%s: ", is_dnf ? "CDNF" : "CCNF");

    if (count == 0) {
        printf("F = %d\n", evaluate(postfix, values));
        return;
    }

    for (unsigned long row = 0; row < (1UL << count); ++row) {
        set_values(row, variables, count, values);
        if (evaluate(postfix, values) != is_dnf) {
            continue;
        }

        if (!first) {
            printf(is_dnf ? " | " : " & ");
        }
        first = 0;
        printf("(");
        for (int i = 0; i < count; ++i) {
            if (i > 0) {
                printf(is_dnf ? " & " : " | ");
            }
            if (values[variables[i]] != is_dnf) {
                printf("!");
            }
            printf("%c", 'A' + variables[i]);
        }
        printf(")");
    }
    if (first)
        printf("F always equals %d",evaluate(postfix, values));
    printf("\n");
}