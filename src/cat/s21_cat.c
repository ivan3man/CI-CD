#include "s21_cat.h"

int main(int argc, char **argv) {
  char flags[N];
  for (int i = 0; i < N; i++) flags[i] = 0;
  int err = 0;
  int count = input(argc, argv, flags);
  if (count >= argc) {
    printf("Input via stdin is not supported\n");
    err = 1;
  }
  if (flags[0] != 0 && err == 0) {
    printf(
        "s21_cat: illegal option -- %c\nusage: s21_cat [-benst] [file ...]\n",
        flags[0]);
    err = 1;
  }
  if (err == 0) {
    for (int i = count; i < argc; i++) {
      err = output(argv[i], flags);
      if (err == 1) printf("s21_cat: %s: No such file or directory\n", argv[i]);
    }
  }
  return 0;
}

int input(int argc, char **argv, char flags[N]) {
  int count = 1;
  char c = '-';
  while (c == '-' && count < argc) {
    c = argv[count][0];
    if (strcmp(argv[count], "--number-nonblank") == 0) {
      flags[1] = 'b';
      flags[3] = 'n';
      count++;
    } else if (strcmp(argv[count], "--number") == 0) {
      flags[3] = 'n';
      count++;
    } else if (strcmp(argv[count], "--squeeze-blank") == 0) {
      flags[4] = 's';
      count++;
    } else if (c == '-') {
      for (int j = 1; argv[count][j] != '\0'; j++) {
        if (argv[count][j] == 'b') {
          flags[1] = 'b';
          flags[3] = 'n';
        } else if (argv[count][j] == 'e') {
          flags[2] = 'e';
          flags[6] = 'v';
        } else if (argv[count][j] == 'E') {
          flags[2] = 'e';
        } else if (argv[count][j] == 'n') {
          flags[3] = 'n';
        } else if (argv[count][j] == 's') {
          flags[4] = 's';
        } else if (argv[count][j] == 't') {
          flags[5] = 't';
          flags[6] = 'v';
        } else if (argv[count][j] == 'T') {
          flags[5] = 't';
        } else if (argv[count][j] == '-' && argv[count][j + 1] == '\0') {
          c = 0;
        } else if (flags[0] == 0)
          flags[0] = argv[count][j];
      }
      count++;
    }
  }
  return count;
}

int output(char *path, char flags[N]) {
  FILE *file = fopen(path, "r");
  if (file == NULL) return 1;
  int s = 1, count = 0;
  char c = 0;
  if (flags[3] == 'n' && fscanf(file, "%c", &c) == 1) {
    if (flags[1] != 'b' || c != '\n') printf("%6d\t", s++);
    fseek(file, -sizeof(char), SEEK_CUR);
  }
  if (flags[4] == 's' && fscanf(file, "%c", &c) == 1) {
    while (c == '\n' && fscanf(file, "%c", &c) == 1) count++;
    fseek(file, -sizeof(char), SEEK_CUR);
    if (c != '\n' && count > 0) fseek(file, -sizeof(char), SEEK_CUR);
  }
  while (fscanf(file, "%c", &c) == 1) {
    if (flags[2] == 'e' && c == '\n') printf("$");
    if (flags[5] == 't' && c == '\t') printf("^I");
    if (flags[6] == 'v' && c < 0) {
      c = toPrintable(c);
    }
    if (flags[6] == 'v' && c != '\t' && c != '\n' && c >= 0 && c < 32)
      printf("^%c", c + 64);
    else if (flags[6] == 'v' && c == 127)
      printf("^%c", c - 64);
    else if (flags[5] != 't' || c != '\t')
      printf("%c", c);
    if (flags[3] == 'n' && c == '\n' && fscanf(file, "%c", &c) == 1) {
      if (flags[1] != 'b' || c != '\n') printf("%6d\t", s++);
      fseek(file, -sizeof(char), SEEK_CUR);
    }
    if (flags[4] == 's' && c == '\n') {
      fscanf(file, "%c", &c);
      if (c == '\n') {
        while (c == '\n' && fscanf(file, "%c", &c) == 1)
          ;
        if (c != '\n') fseek(file, -sizeof(char), SEEK_CUR);
      }
      if (c != '\n')
        fseek(file, -sizeof(char), SEEK_CUR);
      else
        printf("\n");
    }
  }
  fclose(file);
  return 0;
}

char toPrintable(char c) {
  printf("M-");
  c += 128;
  if (c < 32) {
    c += 64;
    printf("^");
  } else if (c == 127) {
    c -= 64;
    printf("^");
  }
  return c;
}