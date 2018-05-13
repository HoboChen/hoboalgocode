#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 100005;
const double eps = 1e-10;

struct node {
    int l, r, sum;
};

node s[maxn * 4];
int n;

void build(int l, int r, int pos) {
    s[pos].l = l;
    s[pos].r = r;
    s[pos].sum = 0;
    if (l == r) return ;
    int m = (l + r) / 2;
    build(l, m, pos * 2);
    build(m + 1, r, pos * 2 + 1);
};

void color(int l, int r, int pos) {
    if (s[pos].l == l && s[pos].r == r) {
        s[pos].sum++;
        return;
    }
    int m = (s[pos].l + s[pos].r) / 2;
    if (m >= r)
        color(l, r, pos * 2);
    else if (m + 1 <= l)
        color(l, r, pos * 2 + 1);
    else {
        color(l, m, pos * 2);
        color(m + 1, r, pos * 2 + 1);
    }
}

void print(int pos, int ans) {
    if (s[pos].l == s[pos].r) {
        if (s[pos].l == 1)
            printf("%d", ans + s[pos].sum);
        else
            printf(" %d", ans + s[pos].sum);
        return;
    }
    print(pos * 2, ans + s[pos].sum);
    print(pos * 2 + 1, ans + s[pos].sum);
    return ;
}


int main() {
    while (scanf("%d", &n) == 1 && n) {
        build(1, n, 1);
        for (int i = 0; i < n; i++) {
            int p, q;
            scanf("%d%d", &p, &q);
            color(p, q, 1);
        }
        print(1, 0);
        printf("\n");
    }
    return 0;
}
