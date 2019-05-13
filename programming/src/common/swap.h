#ifndef COMMON_SWAP_H
#define COMMON_SWAP_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(void* a, void* b, unsigned int len) {
    if (a == b) {
        return;
    }
    void* t = malloc(len);
    memcpy(t, a, len);
    memcpy(a, b, len);
    memcpy(b, t, len);
    free(t);
}

void swap_i(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

#endif
