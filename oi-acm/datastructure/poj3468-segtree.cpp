
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

const double eps = 1e-10;

const int maxn = 100000 + 10000;

struct node {
    long long size, sumv, maxv, minv, addv, setv;

    node (int e = 0) {
        sumv = 0;
        // maxv = 0;
        // minv = 0;
        addv = 0;
        setv = -1;
        size = e;
    }

    void set(int v){
        setv = v;
        // maxv = v;
        // minv = v;
        sumv = v * size;
        addv = 0;
    }

    void add(int v){
        sumv += v * size;
        // maxv += v;
        // minv += v;
        addv += v;
    }
};

node T[3 * maxn];

node operator + (const node & a, const node & b) {
    if (a.size == 0) return b;
    if (b.size == 0) return a;
    node c;
    c.size = a.size + b.size;
    c.sumv = a.sumv + b.sumv;
    // c.maxv = max(a.maxv, b.maxv);
    // c.minv = min(a.minv, b.minv);
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


int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        int t;
        scanf("%d", &t);
        update(1, 1, n, i, i, 2, t);
    }
    for (int i = 0; i < k; i++) {
        getchar();
        char o;
        int l, r;
        scanf("%c%d%d", &o, &l, &r);
        if (o == 'Q') {
            node ans = query(1, 1, n, l, r);
            long long ret = ans.sumv;
            printf("%lld\n", ret);
        }
        if (o == 'C') {
            int c;
            scanf("%d", &c);
            update(1, 1, n, l, r, 1, c);
        }
    }
    return 0;
}
