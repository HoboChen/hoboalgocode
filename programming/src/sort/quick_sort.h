#ifndef SORT_QUICK_SORT_H
#define SORT_QUICK_SORT_H

#include <common/swap.h>

int quick_partition(int* a, int l, int r) {
    int pivot = a[r];
    int i = l;
    int j = l;
    for (; j < r; j++) {
        if (a[j] < pivot) {
            swap_i(&a[i++], &a[j]);
        }
    }
    swap_i(&a[i], &a[j]);
    return i;
}

int quick_sort(int* a, int l, int r) {
    if (l < r) {
        int p = quick_partition(a, l, r);
        quick_sort(a, l, p - 1);
        quick_sort(a, p + 1, r);
    }
}

#endif
