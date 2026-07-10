#ifndef SRC_GREP_TEST_H_
#define SRC_GREP_TEST_H_

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OUTPUT 1024

char *run_s21_grep(char *args);
char *run_grep(char *args);
Suite *s21_grep_suite(void);

#endif  // SRC_GREP_TEST_H_