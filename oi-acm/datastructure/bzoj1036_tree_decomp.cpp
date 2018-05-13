
#include <bits/stdc++.h>

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

const int maxn = 30000 + 1000;
const int maxm = 60000 + 1000;

struct edge { int to, next; };

int head[maxn], fa[maxn];
edge e[maxm]; // the graph

int cnt, sz;
int dep[maxn], size[maxn];
int pos[maxn], top[maxn]; // tree decompiste

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

void read() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", &v[i]);
}

void dfs1(int x) {
    size[x] = 1;
    for (int i = head[x]; i; i=e[i].next) {
        if (e[i].to == fa[x]) continue;
        dep[e[i].to] = dep[x] + 1;
        fa[e[i].to] = x;
        dfs1(e[i].to);
        size[x] += size[e[i].to];
    }
}

void dfs2(int x, int chain) {
    int k = -1;
    pos[x] = ++sz; // assign in seg-tree
    top[x] = chain;
    for (int i = head[x]; i; i = e[i].next)
        if (dep[e[i].to] > dep[x] && size[e[i].to] > size[k])
            k = e[i].to; //
    if (k == -1) return; // TODO
    dfs2(k, chain);
    for (int i = head[x]; i; i = e[i].next)
        if (dep[e[i].to] > dep[x] && k != e[i].to)
            dfs2(e[i].to, e[i].to);
}

int treesum(int x,int y) {
    int ret = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        node ans = query(1, 1, n, pos[top[x]], pos[x]);
        ret += ans.sumv;
        x = fa[top[x]];
    }
    if (pos[x] > pos[y])
        swap(x, y);
    node ans = query(1, 1, n, pos[x], pos[y]);
    ret += ans.sumv;
    return ret;
}

int treemax(int x,int y) {
    int ret = -inf;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        node ans = query(1, 1, n, pos[top[x]], pos[x]);
        ret = max(ret, ans.maxv);
        x = fa[top[x]];
    }
    if (pos[x] > pos[y])
        swap(x, y);
    node ans = query(1, 1, n, pos[x], pos[y]);
    ret = max(ret, ans.maxv);
    return ret;
}

int main() {
    read();
    dfs1(1);
    dfs2(1, 1);
    build(1, 1, n);
    for(int i = 1; i <= n; i++)
        update(1, 1, n, pos[i], pos[i], 2, v[i]);
    scanf("%d", &q);
    char buf[10];
    for(int i = 1; i <= q; i++) {
        int x, y;
        scanf("%s%d%d", buf, &x, &y);
        if (buf[0] == 'C') {
            v[x] = y;
            update(1, 1, n, pos[x], pos[x], 2, y);
        }
        else {
            if (buf[2] == 'A')
                printf("%d\n", treemax(x, y));
            else
                printf("%d\n", treesum(x, y));
        }
    }
    return 0;
}
