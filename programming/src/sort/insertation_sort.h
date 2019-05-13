#ifndef INSERTATION_SORT
#define INSERTATION_SORT

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <helper/swap.h>

void insertation_sort_insert(int* a, int len, int val) {
    a[len] = val;
    int i = len;
    while (i) {
        if (a[i] > a[i - 1]) {
            swap(&a[i], &a[i - 1], sizeof(a[i]));
        }
        i--;
    }
}

void insertation_sort(int* a, int l, int r) {
    int len = l - r + 1;
    int* b = (int*)malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) {
        insertation_sort_insert(b, i, a[i + l]);
    }
    memcpy(a + l, b, len * sizeof(int));
}

#endif