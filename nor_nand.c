#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define NOR_BASIS 0
#define NAND_BASIS 1
#include "nor_nand.h"

char *join(const char *a, char op, const char *b) 
{
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    size_t count = 0;

    char *result = malloc(len_a + len_b + 6);

    if (result == NULL) {
        fprintf(stderr, "Failured to allocate memory.");
        exit(EXIT_FAILURE);
    }

    result[count++] = '(';

    for (size_t i = 0; i < len_a; ++i) {
        result[count++] = a[i];
    }

    result[count++] = ' ';
    result[count++] = op;
    result[count++] = ' ';

    for (size_t i = 0; i < len_b; ++i) {
        result[count++] = b[i];
    }

    result[count++] = ')';
    result[count] = '\0';

    return result;
}

char *make_not(const char *a, int basis)
{
    if (basis == NAND_BASIS) {
        char *result = join(a, '/', a);
        return result;
    } else {
        char *result = join(a, '%', a);
        return result;
    }
}

char *make_or(const char *a, const char *b, int basis)
{
    if (basis == NAND_BASIS) {
        char *left = join(a, '/', a);
        char *right = join(b, '/', b);
        char *result = join(left, '/', right);

        free(left);
        free(right);

        return result;
    } else {
        char *left = join(a, '%', b);
        char *result = join(left, '%', left);

        free(left);

        return result;
    }
}

char *make_and(const char *a, const char *b, int basis)
{
    if (basis == NAND_BASIS) {
        char *left = join(a, '/', b);
        char *result = join(left, '/', left);

        free(left);

        return result;
    } else {
        char *left = join(a, '%', a);
        char *right = join(b, '%', b);
        char *result = join(left, '%', right);

        free(left);
        free(right);
        
        return result;
    }
}

char *make_constant(char value, char *c, int basis) 
{
    char *not_c = make_not(c, basis);
    char *result;

    if (value == '1') {
        result = make_or(c, not_c, basis);
        free(not_c);
        return result;
    } else {
        result = make_and(c, not_c, basis);
        free(not_c);
        return result;
    }
}