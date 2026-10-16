#ifndef NOR_NAND
#define NOR_NAND

char *join(const char *, char, const char *);
char *make_not(const char *, int);
char *make_or(const char *, const char *, int);
char *make_and(const char *, const char *, int);
void print_nor_nand(const char *, int, const int *, int);
char *make_constant(char, char *, int);

#endif