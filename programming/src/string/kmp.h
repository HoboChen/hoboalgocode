#ifndef STRING_KMP_H
#define STRING_KMP_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// int* compute_prefix_function(const char* p) {
//     int m = strlen(p);
//     int* f = malloc(m * sizeof(int));
//     f[0] = 0;
//     int k = 0;
//     for (int q = 1; q < m; q++) {
//         while (k && p[k] != p[q]) {
//             k = f[k];
//         }
//         if (p[k] == p[q]) {
//             k++;
//         }
//         f[q] = k;
//     }
//     return f;
// }

int* compute_prefix_function(const char* p) {
    int m = strlen(p);
    int* f = malloc(m * sizeof(int));
    f[0] = f[1] = 0;
    for (int i = 1; i < m; i++) {
        int j = f[i];
        while (j && p[j] != p[i]) {
            j = f[j];
        }
        f[i + 1] = p[i] == p[j] ? j + 1 : 0;
    }
    return f;
}

void kmp_matcher(const char* s, const char* p) {
    int n = strlen(s);
    int m = strlen(p);
    int* f = compute_prefix_function(p);
    int q = 0;
    for (int i = 0; i < n; i++) {
        while (q && p[q] != s[i]) {
            q = f[q];
        }
        if (p[q] == s[i]) {
            q++;
        }
        if (q == m) {
            printf("%d ", i - m + 1);
        }
    }
}

#endif
