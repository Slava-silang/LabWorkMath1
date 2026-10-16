#include <stdio.h>
#include "basis.h"
#include <stdlib.h>
#define MAX 4096
#define NOR_BASIS 0
#define NAND_BASIS 1
#define MAIN_BASIS 2
#define ZH_BASIS 3


void print_basis(const char *postfix, int count, const int *variables, int basis)
{
    char *stack[MAX];
    int top = 0;

    switch (basis) {
        case NOR_BASIS:
            printf("Your expression in {%%} basis: ");
            break;
        case NAND_BASIS:
            printf("Your expression in {/} basis: ");
            break;
        case MAIN_BASIS:
            printf("Your expression in {|&!} basis: ");
            break;
        case ZH_BASIS:
            printf("Your expression in {^&1} basis: ");
            break;
    }

    for (int i = 0; postfix[i] != '\0'; ++i) {
        char ch = postfix[i];

        if (ch >= 'A' && ch <= 'Z') {
            char *new = malloc(2);
            if (new == NULL) {
                fprintf(stderr, "Failured to allocate memory.");
                exit(EXIT_FAILURE);
            }
            new[0] = ch;
            new[1] = '\0';
            stack[top++] = new;
        } else if (ch == '0' || ch == '1') {
            char letter = count > 0 ? 'A' + variables[0] : 'A';
            char var[2] = {letter, '\0'};
            stack[top++] = make_constant(ch, var, basis);
        } else if (ch == '!') {
            char *old = stack[top - 1];
            stack[top - 1] = make_not(stack[top - 1], basis);
            free(old);
        } else {
            char *result;
            char *second = stack[--top];
            char *first = stack[--top];
            switch(ch) {
                case '|': result = make_or(first, second, basis); break;

                case '&': result = make_and(first, second, basis); break;

                case '^': {
                    if (basis == ZH_BASIS) {
                        result = join(first, '^', second);
                        break;
                    }
                    char *not_first = make_not(first, basis);
                    char *not_second = make_not(second, basis);
                    char *left = make_and(not_first, second, basis);
                    char *right = make_and(first, not_second, basis);
                    result = make_or(left, right, basis);
                    free(not_first);
                    free(not_second);
                    free(left);
                    free(right);
                    break;
                }

                case '=': {
                    char *not_first = make_not(first, basis);
                    char *not_second = make_not(second, basis);
                    char *left = make_and(first, second, basis);
                    char *right = make_and(not_first, not_second, basis);
                    result = make_or(left, right, basis);
                    free(not_first);
                    free(not_second);
                    free(left);
                    free(right);
                    break;
                }

                case '>': {
                    char *not_first = make_not(first, basis);
                    result = make_or(not_first, second, basis);
                    free(not_first);
                    break;
                }

                case '<': {
                    char *not_second = make_not(second, basis);
                    result = make_or(first, not_second, basis);
                    free(not_second);
                    break;
                }

                case '%': {
                    if (basis == NOR_BASIS) {
                        result = join(first, '%', second);
                        break;
                    }
                    char *or = make_or(first, second, basis);
                    result = make_not(or, basis);
                    free(or);
                    break;
                }

                case '/': {
                    if (basis == NAND_BASIS) {
                        result = join(first, '/', second);
                        break;
                    }
                    char *and = make_and(first, second, basis);
                    result = make_not(and, basis);
                    free(and);                
                    break;
                }
            }
            stack[top++] = result;
            free(first);
            free(second);
        }
    }
    printf("%s\n", stack[0]);
    free(stack[0]);
    printf("\n");
}