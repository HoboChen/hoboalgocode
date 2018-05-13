
#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 500 + 50;
const double eps = 1e-10;

int f[maxn][maxn][maxn];
char a[maxn], b[maxn];

const int mod = 1024523;

inline void add(int & t, int d) {
    t += d;
    if (t > mod) t-= mod;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    scanf("%s", a + 1);
    scanf("%s", b + 1);
    reverse(a + 1, a + n + 1);
    reverse(b + 1, b + m + 1);
    f[0][0][0] = 1;
    for (int i1 = 0; i1 <= n; i1++) {
        for (int j1 = 0; j1 <= m; j1++) {
            for (int i2 = 0; i2 <= n; i2++) {
                int j2 = i1 + j1 - i2;
                int & t = f[i1][j1][i2];
                if (j2 < 0 || j2 > m) continue;
                if (a[i1 + 1] == a[i2 + 1]) add(f[i1 + 1][j1][i2 + 1], t);
                if (b[j1 + 1] == b[j2 + 1]) add(f[i1][j1 + 1][i2], t);
                if (a[i1 + 1] == b[j2 + 1]) add(f[i1 + 1][j1][i2], t);
                if (b[j1 + 1] == a[i2 + 1]) add(f[i1][j1 + 1][i2 + 1], t);
            }
        }
    }
    printf("%d\n", f[n][m][n]);
    return 0;
}
