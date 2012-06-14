#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "dbg.h"

#define cfree(p) { if ((p)) free((p)); (p) = NULL; }

typedef int (* compare_cb)(const int, const int);

int inc_order(const int a, const int b);

int dec_order(const int a, const int b);

int oddeven_order(const int a, const int b);

int * bubble_sort(int * source, const int count, compare_cb cmp);

void print_numbers(const int * sorted, const int count);

int test_sorting(int * source, const int count);
