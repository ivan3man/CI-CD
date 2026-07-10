mk=$(abspath $(lastword $(MAKEFILE_LIST)))
cat=$(dir $(mk))
src=$(dir $(abspath $(cat)))

CC=gcc

CFLAGS=-Wall -Werror -Wextra

all: s21_cat test

clean:
	rm $(cat)s21_cat

rebuild: clean all

s21_cat: s21_cat.c
	$(CC) $(CFLAGS) $(cat)$@.c -o $(cat)$@

test: test.c
	$(CC) $(CFLAGS) $(cat)$@.c -lcheck -lm -pthread -lrt -lsubunit -o $(cat)$@