#include "make_postfix.h"
#include <ctype.h>
#ifndef MAX
#define MAX 4096
#endif

int priority(char c)
{
    switch (c)
    {
    case '!':
        return 5;
    case '&': case '/':
        return 4;
    case '|': case '^': case '%':
        return 3;
    case '<': case '>':
        return 2;
    case '=':
        return 1;
    }
    return 0;
}

void make_postfix(const char input[], char postfix[], int used[])
{
    char stack[MAX];
    int top = 0, length = 0;

    for(int i = 0; input[i] != '\0'; ++i) {

        char c = input[i];

        if(isspace((unsigned char)c))
            continue;
        if(c >= 'a' && c <= 'z')
            c = c - 'a' + 'A';
        
        if(c >= 'A' && c <= 'Z') {
            postfix[length++] = c;
            used[c - 'A'] = 1;
        } else if(c == '0' || c == '1') {
            postfix[length++] = c;
        } else if(c == '!' || c == '('){
            stack[top++] = c;
        } else if(c == ')') {
            while (stack[top-1] != '(') {
                postfix[length++] = stack[--top];
            }
            top--;
        } else {

            while (top > 0 && priority(stack[top - 1]) >= priority(c)) {
                postfix[length++] = stack[--top];
            }
            stack[top++] = c;
        }
    }
    while (top > 0) {
        postfix[length++] = stack[--top];
    }
    postfix[length] = '\0';
}