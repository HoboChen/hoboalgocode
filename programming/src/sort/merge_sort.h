#ifndef SORT_MERGE_SORT_H
#define SORT_MERGE_SORT_H

#include <stdio.h>
#include <string.h>

// [l, mid] [mid + 1, r]
void merge(int* a, int l, int r, int mid) {
    int len1 = mid - l + 1;
    int len2 = r - mid;
    int* L = malloc(len1 * sizeof(int));
    int* R = malloc(len2 * sizeof(int));
    memcpy(L, a + l, len1);
    memcpy(R, a + mid + 1, len2);
    int i = 0;
    int j = 0;
    for (int k = l; k <= r; k++) {
        if (L[i] <= R[j]) {
            a[k] = L[i++];
        } else {
            a[k] = R[j++];
        }
    }
}

int merge_sort(int *a, int l, int r) {
    if (l < r) {
        int mid = l + (r - l) / 2;
        merge_sort(a, l, mid);
        merge_sort(a, mid + 1, r);
        merge(a, l, r, mid);
    }
}

#endif

