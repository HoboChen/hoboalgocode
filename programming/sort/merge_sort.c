#include <stdio.h>
#include <string.h>

// [l, mid) [mid, r)
void merge(int* a, int l, int r, int mid) {
    int len1 = mid - l;
    int len2 = r - mid;
    int* L = malloc(len1 * sizeof(int));
    int* R = malloc(len2 * sizeof(int));
    memcpy(L, a + l, len1);
    memcpy(R, a + r, len2);
    int i = 0;
    int j = 0;
    for (int k = l; k < r; k++) {
        if (L[i] <= R[j]) {
            a[k] = L[i++];
        } else {
            a[k] = R[j++];
        }
    }
}

int merge_sort(int* a, int l, int r) {
    if (l + 2 < r) {
        int mid = l + (r - l) / 2;
        merge_sort(a, l, mid);
        merge_sort(a, mid, r);
        merge(a, l, r, mid);
    }
}