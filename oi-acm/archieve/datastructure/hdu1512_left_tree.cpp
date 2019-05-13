#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;
inline void px(string s) { cout << s << ends; }

const int maxn = 200000 + 1000;
const int inf = 0x3e3e3e3e;
const long long llinf = (long long)0x3e3e3e3e * 0x3e3e3e3e;

const double eps = 1e-10;

int p[maxn];

int find(int x, int *p) { return p[x] == x ? x : p[x] = find(p[x], p); }

void merge(int i, int j, int *p) {
    int x = find(i, p), y = find(j, p);
    p[y] = x;
}

void init(int * p, int n) {
    for (int i = 1; i <= n; i++)
        p[i] = i;
}

int n, m;

int tot, v[maxn], l[maxn], r[maxn], d[maxn];
int merge(int x, int y) {
    if (!x) return y;
    if (!y) return x;
    if (v[x] < v[y]) swap(x, y);
    r[x] = merge(r[x], y);
    if (d[l[x]] < d[r[x]]) swap(l[x], r[x]);
    d[x] = d[r[x]] + 1;
    return x;
}

int init(int x) {
    tot++;
    v[tot] = x;
    l[tot] = r[tot] = d[tot] = 0;
    return tot;
}

int insert(int x, int y) { return merge(x, init(y)); }

int top(int x) { return v[x]; };

int pop(int x) { return merge(l[x], r[x]); }

int pos[maxn];

int main() {
    while (scanf("%d", &n) == 1) {
        init(p, n);
        tot = 0;
        for (int i = 1; i <= n; i++) {
            int tmp;
            scanf("%d", &tmp);
            pos[i] = init(tmp);
        }
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            int t1, t2;
            scanf("%d%d", &t1, &t2);
            if (find(t1, p) == find(t2, p)) {
                printf("%d\n", -1);
                continue;
            }
            else {
                int f1 = find(t1, p), f2 = find(t2, p);
                merge(f1, f2, p);
                int mxt1 = top(pos[f1]), mxt2 = top(pos[f2]);
                pos[f1] = pop(pos[f1]), pos[f2] = pop(pos[f2]);
                pos[f1] = insert(pos[f1], mxt1 / 2);
                pos[f2] = insert(pos[f2], mxt2 / 2);
                pos[f1] = merge(pos[f2], pos[f1]); // join x to y
                printf("%d\n", top(pos[f1]));
            }
        }
    }
    return 0;
}
