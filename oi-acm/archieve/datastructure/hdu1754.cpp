#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;
#define inf (0x3e3e3e3e)

const int maxn = 200000 + 10000;
const double eps = 1e-10;

struct node {
    int l, r, xm;
};

node s[maxn * 4];
int f[maxn];

int build(int l, int r, int pos) {
    s[pos].l = l;
    s[pos].r = r;
    if (l == r)
        return s[pos].xm = f[l];
    int m = (l + r) / 2;
    int a = build(l, m, pos * 2);
    int b = build(m + 1, r, pos * 2 + 1);
    return s[pos].xm = max(a, b);
}

int query(int l, int r, int pos) {
    if (s[pos].l > r || s[pos].r < l)
        return -inf;
    if (l <= s[pos].l && r >= s[pos].r)
        return s[pos].xm;
    int a = query(l, r, pos * 2);
    int b = query(l, r, pos * 2 + 1);
    return max(a, b);
}

int update(int tar, int x, int pos) {
    if (tar < s[pos].l || tar > s[pos].r) 
        return s[pos].xm;
    if (s[pos].l == s[pos].r && s[pos].l == tar) 
        return s[pos].xm = x;
    int a = update(tar, x, pos * 2);
    int b = update(tar, x, pos * 2 + 1);
    return s[pos].xm = max(a, b);
}

char buf[100];

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i < n; i++)
            scanf("%d", &f[i + 1]);
        build(1, n, 1);
        char t;
        scanf("%c", &t);
        for (int i = 0; i < m; i++) {
            gets(buf);
            char t;
            int l1, l2;
            sscanf(buf, "%c %d %d", &t, &l1, &l2);
            // pr(t) pr(l1) pr(l2) pn
            if (t == 'Q')
                printf("%d\n", query(l1, l2, 1));
            if (t == 'U') 
                update(l1, l2, 1);
        }
    }

    return 0;
}
