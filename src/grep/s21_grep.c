#include "s21_grep.h"

int main(int argc, char **argv) {
  char flags[N];
  for (int i = 0; i < N; i++) flags[i] = 0;
  char *templates[10 * N];
  for (int i = 0; i < 10 * N; i++) templates[i] = NULL;
  int err = 0;
  int count = input(argc, argv, flags, templates);
  if (count >= argc) {
    printf("Input via stdin is not supported\n");
    err = 1;
  }
  if (flags[0] != 0 && err == 0) {
    printf(
        "s21_grep: illegal option -- %c\nusage: s21_grep [options] template "
        "[file ...]\n",
        flags[0]);
    err = 1;
  }
  if (templates[0] == NULL && err == 0) {
    printf("s21_grep: option requires an argument -- 'e'\n");
    err = 1;
  }
  if (err == 0 && !(flags[2] == 'v' && flags[8] == 'o' && flags[4] != 'l' &&
                    flags[3] != 'c')) {
    for (int i = count; i < argc; i++) {
      err = output(argv[i], flags, templates, count < argc - 1 ? 1 : 0);
      if (err == 1 && flags[7] != 's')
        printf("s21_grep: %s: No such file or directory\n", argv[i]);
    }
  }
  if (flags[9] == 'f') {
    count = 0;
    while (templates[count] && count < 10 * N) free(templates[count++]);
  }
  return 0;
}

int input(int argc, char **argv, char flags[N], char *templates[10 * N]) {
  int count = 1, temp = 0;
  char c = '-';
  while (c == '-' && count < argc) {
    c = argv[count][0];
    if (c == '-') {
      for (int j = 1; argv[count][j] != '\0'; j++) {
        if (argv[count][j] == 'i') {
          flags[1] = 'i';
        } else if (argv[count][j] == 'v') {
          flags[2] = 'v';
        } else if (argv[count][j] == 'c') {
          flags[3] = 'c';
        } else if (argv[count][j] == 'l') {
          flags[4] = 'l';
        } else if (argv[count][j] == 'n') {
          flags[5] = 'n';
        } else if (argv[count][j] == 'h') {
          flags[6] = 'h';
        } else if (argv[count][j] == 's') {
          flags[7] = 's';
        } else if (argv[count][j] == 'o') {
          flags[8] = 'o';
        } else if (argv[count][j] == 'f') {
          flags[9] = 'f';
          fFlag(argv[++count], templates, temp);
          j = strlen(argv[count]) - 1;
        } else if (argv[count][j] == '-' && argv[count][j + 1] == '\0') {
          c = 0;
        } else if (argv[count][j] == 'e') {
          if (argv[count][j + 1] == '\0' && count < argc - 1 && temp < 10 * N)
            templates[temp++] = argv[++count];
          else if (argv[count][j + 1] != '\0' && temp < 10 * N)
            templates[temp++] = &(argv[count][j + 1]);
          j = strlen(argv[count]) - 1;
        } else if (flags[0] == 0)
          flags[0] = argv[count][j];
      }
      count++;
    } else if (templates[0] == NULL)
      templates[temp++] = argv[count++];
    else
      c = 0;
    if (c != 0) c = '-';
  }
  if (templates[0] == NULL && count < argc - 1) templates[0] = argv[count++];
  return count;
}

int output(char *path, char flags[N], char *templates[10 * N], char fileS) {
  FILE *file = fopen(path, "r");
  if (file == NULL) return 1;
  const char *error = NULL;
  int erroffset = 0, rc = 0, lines = 0, matches = 0, eof = 0, count = 0, tr = 0,
      len = 0, ovector[N * 3];
  char line[N * 100];
  pcre *re[10 * N];
  for (int i = 0; i < 10 * N; i++) re[i] = NULL;
  while (templates[count] != NULL) {
    re[count] =
        pcre_compile(templates[count], flags[1] == 'i' ? PCRE_CASELESS : 0,
                     &error, &erroffset, NULL);
    count++;
  }
  while (fgets(line, sizeof(line), file)) {
    eof = 0, count = 0, len = strlen(line), lines++;
    while (re[count] != NULL) {
      rc = pcre_exec(re[count++], NULL, line, len, 0, 0, ovector, N * 3);
      if ((rc >= 0 && flags[2] != 'v') || (rc < 0 && flags[2] == 'v'))
        tr = count;
    }
    if (tr > 0) {
      if (flags[3] != 'c' && flags[4] != 'l') {
        if (flags[6] != 'h' && fileS) printf("%s:", path);
        if (flags[5] == 'n') printf("%d:", lines);
        if (flags[8] == 'o')
          oFlag(line, lines, flags, fileS, path, len, ovector, re[tr - 1]);
        else
          printf("%s", line);
        eof = 1;
      }
      tr = 0, matches++;
    }
  }
  if (flags[4] == 'l' && matches > 0)
    printf("%s\n", path);
  else if (flags[3] == 'c') {
    if (fileS) printf("%s:", path);
    printf("%d\n", matches);
  } else if (!flags[4] && eof == 1)
    printf("\n");
  for (int i = 0; i < 10 * N; i++) pcre_free(re[i]);
  fclose(file);
  return 0;
}

void fFlag(char *path, char *templates[10 * N], int temp) {
  FILE *file = fopen(path, "r");
  if (file == NULL) return;
  char line[N * 100];
  while (fgets(line, sizeof(line), file) && temp < 10 * N) {
    templates[temp] = (char *)malloc((strlen(line) + 1) * sizeof(char));
    strncpy(templates[temp++], line, strlen(line) + 1);
  }
  fclose(file);
}

void oFlag(char *line, int lines, char flags[N], int fileS, char *path, int len,
           int ov[N * 3], pcre *re) {
  printf("%.*s\n", ov[1] - ov[0], line + ov[0]);
  for (int i = ov[0]; i < ov[1]; i++) line[i] = 0;
  int rc = pcre_exec(re, NULL, line, len, 0, 0, ov, N * 3);
  while ((rc >= 0 && flags[2] != 'v') || (rc < 0 && flags[2] == 'v')) {
    if (flags[6] != 'h' && fileS) printf("%s:", path);
    if (flags[5] == 'n') printf("%d:", lines);
    printf("%.*s\n", ov[1] - ov[0], line + ov[0]);
    for (int i = ov[0]; i < ov[1]; i++) line[i] = 0;
    rc = pcre_exec(re, NULL, line, len, 0, 0, ov, N * 3);
  }
}