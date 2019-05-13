#ifndef SWAP_H
#define DEFINE SWAP_H

#include <string.h>
#include <stdlib.h>

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

#endif