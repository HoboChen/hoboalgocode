#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int inf = 0x3e3e3e3e;

const int maxn = 20000 + 1000;
const int maxm = 400000 + 1000;

struct edge { int to, next; };

int head[maxn], fa[maxn];
edge e[maxm]; // the graph

int cnt, sz;
int dep[maxn], size[maxn];
int pos[maxn], top[maxn], son[maxn]; // tree decompiste

int n, q;
int v[maxn]; // this problem

inline void addedge(int u, int v) {
    e[++cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
    e[++cnt].to = u;
    e[cnt].next = head[v];
    head[v] = cnt;
}

void dfs1(int u) {
    size[u] = 1;
    for (int i = head[u]; i; i=e[i].next) {
        int v = e[i].to;
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1;
        fa[v] = u;
        dfs1(v);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}

int adx[maxn];

void dfs2(int x, int chain) {
    int k = -1;
    pos[x] = ++sz; // assign in seg-tree
    top[x] = chain;
    for (int i = head[x]; i; i = e[i].next)
        if (dep[e[i].to] > dep[x] && size[e[i].to] > size[k])
            k = e[i].to;  
    if (k == -1) return; 
    dfs2(k, chain);
    for (int i = head[x]; i; i = e[i].next)
        if (dep[e[i].to] > dep[x] && k != e[i].to)
            dfs2(e[i].to, e[i].to);
}

void treeadd(int x, int y, int d) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) 
            swap(x, y);
        adx[pos[top[x]]] += d; // segtree interval is [pos[top[x]], pos[x]]
        adx[pos[x] + 1] -= d;
        x = fa[top[x]];
    }
    if (x == y) return; // for edge
    if (dep[x] > dep[y])
        swap(x, y);
    adx[pos[son[x]]] += d; // segtree interval is [pos[son[x]], pos[y]]
    adx[pos[y] + 1] -= d;
}

void init() {
    cnt = sz = 0;
    memset(head, 0, sizeof(head));
    memset(adx, 0, sizeof(adx));
    memset(son, 0, sizeof(son));
}

void treedecompprint() {
    for (int i = 1; i <= n; i++) 
        printf("%d %d %d\n", pos[i], son[i], dep[i]);
}

void idxprint() {
    for (int i = 1; i <= n; i++) {
        printf("%d\n", adx[i]);
    }
}

int main() {
    int m, c = 0;
    int t;
    scanf("%d", &t);
    while (t--) {
        init();
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n - 1; i++) {
            int t1, t2;
            scanf("%d%d", &t1, &t2);
            addedge(t1, t2);
        }
        dfs1(1);
        dfs2(1, 1);
        // treedecompprint();
        for (int i = 0; i < m - n + 1; i++) {
            int t1, t2;
            scanf("%d%d", &t1, &t2);
            treeadd(t1, t2, 1);
        }
        // idxprint();
        int ans = inf;
        for (int i = 2; i <= n; i++) {
            adx[i] += adx[i - 1];
            if (i > 1) ans = min(ans, adx[i]);
        }
        printf("Case #%d: %d\n", ++c, ans + 1);
    }
    return 0;
}
