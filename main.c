#include <stdio.h>
#include "make_postfix.h"
#include "normal_form.h"
#include "print_table.h"
#include "fictive.h"
#include "basis.h"
#define MAX 4096
#define NOR_BASIS 0
#define NAND_BASIS 1
#define MAIN_BASIS 2
#define ZH_BASIS 3

int main(int argc, char *argv[])
{
    int used[26] = {0};
    char postfix[MAX];
    char input[MAX];
    int variables[26] = {0};

    int length = 0;
    int count = 0;
    int ch;

    if(argc < 2) {
        fprintf(stderr, "Error: file path cannot be empty");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if(file == NULL){
        fprintf(stderr, "Cannot open the file");
        fclose(file);
        return 1;
    }

    while ((ch = fgetc(file)) != EOF){
        if (length > MAX-1){
            fprintf(stderr, "File is too big");
            fclose(file);
            return 1;
        }
        input[length++] = (char)ch;
    }

    fclose(file);

    input[length] = '\0';

    make_postfix(input, postfix, used);

    for(int i = 0; i < 26; ++i){
        if(used[i])
            variables[count++] = i;
    }
    print_table(postfix, variables, count);
    print_normal_form(postfix, variables, count, 1);
    print_normal_form(postfix, variables, count, 0);
    print_fictitious_var(postfix, variables, count);
    print_basis(postfix, count, variables, NOR_BASIS);
    print_basis(postfix, count, variables, NAND_BASIS);
    print_basis(postfix, count, variables, MAIN_BASIS);
    print_basis(postfix, count, variables, ZH_BASIS);

    return 0;
}