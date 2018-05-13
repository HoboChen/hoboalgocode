
#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 150 + 10;
const double eps = 1e-10;

const int inf = 0x3e3e3e3e;

int a[maxn];
int f[2][maxn][maxn * maxn];

int main() {
    int n, K, s;
    scanf("%d%d%d", &n, &K, &s);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i + 1]);
    }
    if (s >= (n * (n - 1) / 2)) {
        sort(a + 1, a + n + 1);
        int ans = 0;
        for (int i = 0; i < K; i++) 
            ans += a[i + 1];
        printf("%d", ans);
        return 0;
    }
    int mu = s + K * (K + 1) / 2;
    memset(f, 0x3e3e3e3e, sizeof(f));
    f[0][0][0] = f[1][0][0] = 0;
    f[1][1][1] = a[1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= min(i, K); j++) {
            for (int l = 0; l <= mu; l++) {
                if (l - i >= 0) 
                    f[i % 2][j][l] = f[(i + 1) % 2][j - 1][l - i] + a[i];
                f[i % 2][j][l] = min(f[(i + 1) % 2][j][l], f[i % 2][j][l]);
            }
        }
    }
    int ans = inf;
    for (int i = 0; i <= mu; i++)
        ans = min(ans, f[n % 2][K][i]);
    printf("%d", ans);

    return 0;
}
