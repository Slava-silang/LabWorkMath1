#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define NOR_BASIS 0
#define NAND_BASIS 1
#define MAIN_BASIS 2
#define ZH_BASIS 3
#include "basis.h"

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
    } else if (basis == NOR_BASIS) {
        char *result = join(a, '%', a);
        return result;
    } else if (basis == MAIN_BASIS) {
        size_t len_a = strlen(a);
        char *result = malloc(len_a + 2);
        if (result == NULL) {
            fprintf(stderr, "Failured to allocate memory.");
            exit(EXIT_FAILURE);
        }
        int count = 0;
        result[count++] = '!';
        for (size_t i = 0; i < len_a; ++i) {
            result[count++] = a[i];
        }
        result[count] = '\0';
        return result;
    } else {
        char one[2] = {'1', '\0'};
        char *result = join(a, '^', one);
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
    } else if(basis == NOR_BASIS) {
        char *left = join(a, '%', b);
        char *result = join(left, '%', left);

        free(left);

        return result;
    } else if (basis == MAIN_BASIS) {
        char *result = join(a, '|', b);
        return result;
    } else {
        char *left = join(a, '^', b);
        char *right = join(a, '&', b);
        char *result = join(left, '^', right);
        free(left);
        free(right);
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
    } else if (basis == NOR_BASIS) {
        char *left = join(a, '%', a);
        char *right = join(b, '%', b);
        char *result = join(left, '%', right);

        free(left);
        free(right);
        
        return result;
    } else if (basis == MAIN_BASIS) {
        char *result = join(a, '&', b);
        return result;
    } else {
        char *result = join(a, '&', b);
        return result;
    }
}

char *make_constant(char value, char *c, int basis) 
{
    char *not_c = make_not(c, basis);
    char *result;

    if (basis == ZH_BASIS) {
        if (value == '1') {
            result = malloc(2);
            result[0] = '1';
            result[1] = '\0';
            return result;
            return result;
        } else {
            char one[2] = {'1', '\0'};
            result = join(one, '^', one);
            return result;
        }
    }

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