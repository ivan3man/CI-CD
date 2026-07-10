mk=$(abspath $(lastword $(MAKEFILE_LIST)))
grep=$(dir $(mk))
src=$(dir $(abspath $(grep)))

CC=gcc

CFLAGS=-Wall -Werror -Wextra

all: s21_grep test

clean:
	rm $(grep)s21_grep

rebuild: clean all

s21_grep: s21_grep.c
	$(CC) $(CFLAGS) $(grep)$@.c -o $(grep)$@ -lpcre

test: test.c
	$(CC) $(CFLAGS) $(grep)$@.c -lcheck -lm -pthread -lrt -lsubunit -o $(grep)$@