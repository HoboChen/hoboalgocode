// #include <bits/stdc++.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxl = 400;
const int maxw = 600 + 100;
const int maxwl = 25 + 5;
const double eps = 1e-10;

char s[maxl];
char t[maxw][maxwl];
int dp[maxl];

int main() {
    int w, l;
    while (scanf("%d%d", &w, &l) == 2) {
        scanf("%s", s);
        for (int i = 0; i < w; i++) {
            scanf("%s", t[i]);
        }
        dp[l] = 0;
        for (int i = l - 1; i >= 0; i--) {
            dp[i] = dp[i + 1] + 1;
            for (int j = 0; j < w; j++) {
                int len = strlen(t[j]);
                if (len <= l - i && t[j][0] == s[i]) {
                    int posm = i;
                    int posw = 0;
                    while (posm < l) {
                        if (t[j][posw] == s[posm++])
                            posw++;
                        if (posw == len) {
                            dp[i] = min(dp[i], dp[posm] + posm - i - len);
                            break;
                        }
                    }
                }
            }
        }
        printf("%d\n", dp[0]);
    }
    return 0;
}
