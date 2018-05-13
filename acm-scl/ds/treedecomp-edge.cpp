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

const int maxnode = 100000 + 10000;

struct node {
    int size, sumv, maxv, addv, setv;

    node (int e = 0) {
        sumv = 0;
        maxv = 0;
        addv = 0;
        setv = -1;
        size = e;
    }

    void set(int v){
        setv = v;
        maxv = v;
        sumv = v * size;
        addv = 0;
    }

    void add(int v){
        sumv += v * size;
        maxv += v;
        addv += v;
    }
};

node T[3 * maxnode];

node operator + (const node & a, const node & b) {
    if (a.size == 0) return b;
    if (b.size == 0) return a;
    node c;
    c.size = a.size + b.size;
    c.sumv = a.sumv + b.sumv;
    c.maxv = max(a.maxv, b.maxv);
    return c;
}

void mark(int o, int op, int val) {
    if (op == 1) T[o].add(val);
    else T[o].set(val);
}

void pushdown(int o) {
    if (T[o].setv != -1){
        mark(2 * o, 2, T[o].setv);
        mark(2 * o + 1, 2, T[o].setv);
    }
    mark(2 * o, 1, T[o].addv);
    mark(2 * o + 1, 1, T[o].addv);
    T[o].addv = 0;
    T[o].setv = -1;
}

void update(int o, int l, int r, int a, int b, int op, int val) {
    if (l > b || r < a)
        return;
    if (a <= l && r <= b) {
        mark(o, op, val);
        return;
    }
    pushdown(o);
    int m = (l + r) / 2;
    if (a > m) {
        update(2 * o + 1, m + 1, r, a, b, op, val);
        T[o] = T[2 * o] + T[2 * o + 1];
        return;
    }
    if (b <= m) {
        update(2 * o, l, m, a, b, op, val);
        T[o] = T[2 * o] + T[2 * o + 1];
        return;
    }
    update(2 * o, l, m, a, b, op, val);
    update(2 * o + 1, m + 1, r, a, b, op, val);
    T[o] = T[2 * o] + T[2 * o + 1];
}

node query(int o, int l, int r, int a, int b) {
    if (l > b || r < a)
        return node(0);
    if (a <= l && r <= b)
        return T[o];
    pushdown(o);
    int m = (l + r) / 2;
    if (a > m)
        return query(2 * o + 1, m + 1, r, a, b);
    if (b <= m)
        return query(2 * o, l, m, a, b);
    return query(2 * o, l, m, a, b) + query(2 * o + 1, m + 1, r, a, b);
}

void build(int o, int l, int r) {
    if (l == r)
        T[o] = node(1);
    else {
        build(2 * o, l, (l + r) / 2);
        build(2 * o + 1, (l + r) / 2 + 1, r);
        T[o] = T[2 * o] + T[2 * o + 1];
    }
}

// query [l, r] support max, min and sum
// set [l, r] to val, op = 2
// add [l, r] a val, op = 1


const int inf = 0x3e3e3e3e;

const int maxn = 100000 + 10000;
const int maxm = 200000 + 10000;

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

void treeset(int x, int y, int d) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        update(1, 1, n, pos[top[x]], pos[x], 2, d); // segtree interval is [pos[top[x]], pos[x]]
        x = fa[top[x]];
    }
    if (x == y) return; // for edge
    if (dep[x] > dep[y])
        swap(x, y);
    update(1, 1, n, pos[son[x]], pos[y], 2, d);
}

int treesum(int x, int y) {
    int ret = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        node ans = query(1, 1, n, pos[top[x]], pos[x]); // segtree interval is [pos[top[x]], pos[x]]
        ret += ans.sumv;
        x = fa[top[x]];
    }
    if (x == y) return ret; // for edge
    if (dep[x] > dep[y])
        swap(x, y);
    node ans = query(1, 1, n, pos[son[x]], pos[y]); // segtree interval is [pos[son[x]], pos[y]]
    ret += ans.sumv;
    return ret;
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

int uu[maxn], vv[maxn], ww[maxn];

int main() {
    int start;
    init();
    scanf("%d%d%d", &n, &q, &start);
    for (int i = 1; i <= n - 1; i++) {
        scanf("%d%d%d", &uu[i], &vv[i], &ww[i]);
        addedge(uu[i], vv[i]);
    }
    dfs1(1);
    dfs2(1, 1);
    build(1, 1, n);
    for (int i = 1; i <= n - 1; i++)
        treeset(uu[i], vv[i], ww[i]);
    for (int i = 1; i <= q; i++) {
        int opr;
        scanf("%d", &opr);
        if (opr == 0) {
            int dest;
            scanf("%d", &dest);
            printf("%d\n", treesum(start, dest));
            start = dest;
        }
        if (opr == 1) {
            int num, wx;
            scanf("%d%d", &num, &wx);
            treeset(uu[num], vv[num], wx);
        }
    }
    return 0;
}
