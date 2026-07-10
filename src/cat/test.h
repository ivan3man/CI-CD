#ifndef SRC_CAT_TEST_H_
#define SRC_CAT_TEST_H_

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OUTPUT 1024

char *run_s21_cat(char *args);
char *run_cat(char *args);
Suite *s21_cat_suite(void);

#endif  // SRC_CAT_TEST_H_