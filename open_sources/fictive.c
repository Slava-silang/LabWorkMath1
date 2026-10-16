#include <stdio.h>
#include "fictive.h"
#include "set_values.h"
#include "calculator.h"

void print_fictitious_var(const char postfix[], const int variables[], int count)
{
    int values[26] = {0};
    int found = 0;

    printf("Fictitious variables: ");

    for (int i = 0; i < count; ++i) {
        int variable = variables[i];
        int fictitious = 1;

        for (unsigned long row = 0; row < (1UL << count); ++row){
            set_values(row, variables, count, values);
            if (values[variables[i]] != 0)
                continue;
            int before = evaluate(postfix, values);
            values[variables[i]] = 1;
            int after = evaluate(postfix, values);
            if (before != after) {
                fictitious = 0;
                break;
            }
        }
        if (fictitious) {
            printf("%c ", 'A' + variable);
            found = 1;
        }
    }
    if (!found) {
        printf("There are no fictitious variables.");
    }
    printf("\n");
}