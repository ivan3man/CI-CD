#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 7

int input(int argc, char **argv, char flags[N]);
int output(char *path, char flags[N]);
char toPrintable(char c);

#endif  // SRC_CAT_S21_CAT_H_