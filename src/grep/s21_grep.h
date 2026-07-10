#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

int input(int argc, char **argv, char flags[N], char *templates[10 * N]);
int output(char *path, char flags[N], char *templates[10 * N], char fileS);
void fFlag(char *path, char *templates[10 * N], int temp);
void oFlag(char *line, int lines, char flags[N], int fileS, char *path, int len,
           int ov[N * 3], pcre *re);

#endif  // SRC_GREP_S21_GREP_H_