#ifndef BATHIS
#define BATHIS

char *join(const char *, char, const char *);
char *make_not(const char *, int);
char *make_or(const char *, const char *, int);
char *make_and(const char *, const char *, int);
void print_basis(const char *, int, const int *, int);
char *make_constant(char, char *, int);

#endif