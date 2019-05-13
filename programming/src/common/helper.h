#ifndef COMMON_HELPER
#define COMMON_HELPER

#include <stdlib.h>
#include <stdbool.h>

bool is_ascending_order(int* a, int l, int r) {
    if (l >= r) {
        exit(-1); // fatal
    }
    for (int i = l; i < r - 1; i++) {
        if (a[i] > a[i + 1]) {
            return false;
        }
    }
    return true;
}

bool is_descending_order(int* a, int l, int r) {
    if (l >= r) {
        exit(-1); // fatal
    }
    for (int i = l; i < r - 1; i++) {
        if (a[i] < a[i + 1]) {
            return false;
        }
    }
    return true;
}

#endif
