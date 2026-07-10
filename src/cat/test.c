#include "test.h"

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;
  s = s21_cat_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

char *run_s21_cat(char *args) {
  char cmd[MAX_OUTPUT];
  snprintf(cmd, MAX_OUTPUT, "./s21_cat %s", args);
  FILE *fp = popen(cmd, "r");
  if (fp == NULL) {
    printf("Failed to run command\n");
    exit(1);
  }
  static char output[MAX_OUTPUT];
  int i = 0, c = 0;
  while ((c = fgetc(fp)) != EOF && i < MAX_OUTPUT - 1) {
    output[i++] = c;
  }
  output[i] = '\0';
  pclose(fp);
  return output;
}

char *run_cat(char *args) {
  char cmd[MAX_OUTPUT];
  snprintf(cmd, MAX_OUTPUT, "cat %s", args);
  FILE *fp = popen(cmd, "r");
  if (fp == NULL) {
    printf("Failed to run command\n");
    exit(1);
  }
  static char output[MAX_OUTPUT];
  int i = 0, c = 0;
  while ((c = fgetc(fp)) != EOF && i < MAX_OUTPUT - 1) {
    output[i++] = c;
  }
  output[i] = '\0';
  pclose(fp);
  return output;
}

START_TEST(test_s21_cat_b_flag) {
  char *args = "-b data-samples/test.txt";
  ck_assert_str_eq(run_s21_cat(args), run_cat(args));
}
END_TEST

START_TEST(test_s21_cat_e_flag) {
  char *args = "-e data-samples/test.txt";
  ck_assert_str_eq(run_s21_cat(args), run_cat(args));
}
END_TEST

START_TEST(test_s21_cat_n_flag) {
  char *args = "-n data-samples/test.txt";
  ck_assert_str_eq(run_s21_cat(args), run_cat(args));
}
END_TEST

START_TEST(test_s21_cat_s_flag) {
  char *args = "-s data-samples/test.txt";
  ck_assert_str_eq(run_s21_cat(args), run_cat(args));
}
END_TEST

START_TEST(test_s21_cat_t_flag) {
  char *args = "-t data-samples/test.txt";
  ck_assert_str_eq(run_s21_cat(args), run_cat(args));
}
END_TEST

START_TEST(test_s21_cat_nn_flag) {
  char *args = "--number-nonblank data-samples/test.txt";
  ck_assert_str_eq(run_s21_cat(args), run_cat(args));
}
END_TEST

START_TEST(test_s21_cat_E_flag) {
  char *args = "-E data-samples/test.txt";
  ck_assert_str_eq(run_s21_cat(args), run_cat(args));
}
END_TEST

START_TEST(test_s21_cat_num_flag) {
  char *args = "--number data-samples/test.txt";
  ck_assert_str_eq(run_s21_cat(args), run_cat(args));
}
END_TEST

START_TEST(test_s21_cat_sb_flag) {
  char *args = "--squeeze-blank data-samples/test.txt";
  ck_assert_str_eq(run_s21_cat(args), run_cat(args));
}
END_TEST

START_TEST(test_s21_cat_T_flag) {
  char *args = "-T data-samples/test.txt";
  ck_assert_str_eq(run_s21_cat(args), run_cat(args));
}
END_TEST

START_TEST(test_s21_cat_all_flag) {
  char *args = "-benst data-samples/test.txt";
  ck_assert_str_eq(run_s21_cat(args), run_cat(args));
}
END_TEST

Suite *s21_cat_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_cat");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_s21_cat_b_flag);
  tcase_add_test(tc_core, test_s21_cat_e_flag);
  tcase_add_test(tc_core, test_s21_cat_n_flag);
  tcase_add_test(tc_core, test_s21_cat_s_flag);
  tcase_add_test(tc_core, test_s21_cat_t_flag);
  tcase_add_test(tc_core, test_s21_cat_nn_flag);
  tcase_add_test(tc_core, test_s21_cat_E_flag);
  tcase_add_test(tc_core, test_s21_cat_num_flag);
  tcase_add_test(tc_core, test_s21_cat_sb_flag);
  tcase_add_test(tc_core, test_s21_cat_T_flag);
  tcase_add_test(tc_core, test_s21_cat_all_flag);
  suite_add_tcase(s, tc_core);
  return s;
}