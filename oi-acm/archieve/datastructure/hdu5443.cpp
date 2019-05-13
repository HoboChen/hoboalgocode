
#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 1000 + 100;
const double eps = 1e-10;

int st[maxn][14], n, a[maxn];

void getST() {
    int m = log(n) / log(2);
    for (int i = 1; i <= n; i++)
        st[i][0] = i;
    for (int j = 1; j <= m; j++)
        for (int i = n; i > 0; i--) {
            // st[i][j] = st[i][j - 1];
            // if (i + (1 << (j - 1)) <= n)
                // st[i][j] = max(st[i][j], st[i + (1 << (j - 1))][j - 1]);
            st[i][j] = (a[st[i][j - 1]] > a[st[i + (1 << (j - 1))][j - 1]]) ? st[i][j - 1] : st[i + (1 << (j - 1))][j - 1];
    }
}

int query(int l, int r) {
    int k = log(r - l + 1) / log(2);
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        getST();
        int q;
        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", query(l, r));
        }
    }
    return 0;
}
