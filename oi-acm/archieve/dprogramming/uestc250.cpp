
#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 1000;
const double eps = 1e-10;

int f[20][20];

void getDP() {
    memset(f, 0, sizeof(f));
    for (int i = 0; i <= 9; i++) 
        f[1][i] = 1;
    for (int i = 2; i <= 10; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) {
                if (abs(k - j) > 1)
                    f[i][j] += f[i - 1][k];
            }
        }
    }
}

long long getANS(int x) {
    long long ret = 0;
    int t[12];
    memset(t, 0, sizeof(t));
    int len = 1;
    while (x) {
        t[len++] = x % 10;
        x /= 10;
    }
    len--;
    for (int i = 1; i <= len - 1; i++)
        for (int j = 1; j <= 9; j++) 
            ret += f[i][j];
    for (int i = 1; i < t[len]; i++) 
        ret += f[len][i];
    for (int i = len - 1; i >= 1; i--) {
        for (int j = 0; j < t[i]; j++) {
            if (abs(t[i + 1] - j) > 1)
                ret += f[i][j];
        }
        if (abs(t[i + 1] - t[i]) <= 2) 
            break;
    }
    return ret;
}

int main() {
    getDP();
    int l, r;
    while (scanf("%d%d", &l, &r) == 2) {
        printf("%lld\n", getANS(r + 1)  - getANS(l));
    }
    return 0;
}
