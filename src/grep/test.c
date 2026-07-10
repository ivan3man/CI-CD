#include "test.h"

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;
  s = s21_grep_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

char *run_s21_grep(char *args) {
  char cmd[MAX_OUTPUT];
  snprintf(cmd, MAX_OUTPUT, "./s21_grep %s", args);
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

char *run_grep(char *args) {
  char cmd[MAX_OUTPUT];
  snprintf(cmd, MAX_OUTPUT, "grep %s", args);
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

START_TEST(test_s21_grep_e_flag) {
  char *args = "-e b -e x data-samples/test.txt s21_grep.c";
  ck_assert_str_eq(run_s21_grep(args), run_grep(args));
}
END_TEST

START_TEST(test_s21_grep_i_flag) {
  char *args = "a -i data-samples/test.txt s21_grep.c";
  ck_assert_str_eq(run_s21_grep(args), run_grep(args));
}
END_TEST

START_TEST(test_s21_grep_v_flag) {
  char *args = "a -v data-samples/test.txt s21_grep.c";
  ck_assert_str_eq(run_s21_grep(args), run_grep(args));
}
END_TEST

START_TEST(test_s21_grep_c_flag) {
  char *args = "a -c data-samples/test.txt s21_grep.c";
  ck_assert_str_eq(run_s21_grep(args), run_grep(args));
}
END_TEST

START_TEST(test_s21_grep_l_flag) {
  char *args = "a -l data-samples/test.txt s21_grep.c";
  ck_assert_str_eq(run_s21_grep(args), run_grep(args));
}
END_TEST

START_TEST(test_s21_grep_n_flag) {
  char *args = "a -n data-samples/test.txt s21_grep.c";
  ck_assert_str_eq(run_s21_grep(args), run_grep(args));
}
END_TEST

START_TEST(test_s21_grep_h_flag) {
  char *args = "a -h data-samples/test.txt s21_grep.c";
  ck_assert_str_eq(run_s21_grep(args), run_grep(args));
}
END_TEST

START_TEST(test_s21_grep_s_flag) {
  char *args = "a -s data-samples/test.txt data-samples/test2.txt";
  ck_assert_str_eq(run_s21_grep(args), run_grep(args));
}
END_TEST

START_TEST(test_s21_grep_o_flag) {
  char *args = "a -o data-samples/test.txt s21_grep.c";
  ck_assert_str_eq(run_s21_grep(args), run_grep(args));
}
END_TEST

START_TEST(test_s21_grep_f_flag) {
  char *args = "-f data-samples/test.txt s21_grep.c";
  ck_assert_str_eq(run_s21_grep(args), run_grep(args));
}
END_TEST

START_TEST(test_s21_grep_all_flag) {
  char *args = "-e b -e x -ivclnhso data-samples/test.txt s21_grep.c";
  ck_assert_str_eq(run_s21_grep(args), run_grep(args));
}
END_TEST

Suite *s21_grep_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_grep");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_s21_grep_e_flag);
  tcase_add_test(tc_core, test_s21_grep_i_flag);
  tcase_add_test(tc_core, test_s21_grep_v_flag);
  tcase_add_test(tc_core, test_s21_grep_c_flag);
  tcase_add_test(tc_core, test_s21_grep_l_flag);
  tcase_add_test(tc_core, test_s21_grep_n_flag);
  tcase_add_test(tc_core, test_s21_grep_h_flag);
  tcase_add_test(tc_core, test_s21_grep_s_flag);
  tcase_add_test(tc_core, test_s21_grep_o_flag);
  tcase_add_test(tc_core, test_s21_grep_f_flag);
  tcase_add_test(tc_core, test_s21_grep_all_flag);
  suite_add_tcase(s, tc_core);
  return s;
}