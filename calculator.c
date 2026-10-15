#include "calculator.h"
#ifndef MAX
#define MAX 4096
#endif

int evaluate(const char postfix[], const int values[])
{
    int stack[MAX];
    int top = 0;

    for (int i = 0; postfix[i] != '\0'; ++i) {
        char c = postfix[i];

        if (c >= 'A' && c <= 'Z') {
            stack[top++] = values[c - 'A'];
        } else if (c == '!') {
            stack[top - 1] = !stack[top - 1];
        } else if (c == '0' || c == '1') {
            stack[top++] = c - '0';
        } else {
            int second = stack[--top];
            int first = stack[--top];
            int result = 0;

            switch (c) {
                case '&': result = first && second; break;
                case '|': result = first || second; break;
                case '^': result = first != second; break;
                case '=': result = first == second; break;
                case '>': result = first <= second; break;
                case '<': result = second <= first; break;
                case '%': result = !(first || second); break;
                case '/': result = !(first && second); break;
            }
            stack[top++] = result;
        }
    }
    return stack[0];
}