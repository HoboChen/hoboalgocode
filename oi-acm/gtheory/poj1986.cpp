#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <deque>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <stack>
#include <deque>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <climits>


using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;
#define px cout << "$$$$$" << ends;

const int maxn = 100000;
const int maxm = 200000;
const int inf = 0x3e3e3e3e;
struct edge { int to, next, dist; };

edge e[maxm];
int head[maxn], tot;

void addedge(int u, int v, int w) {
    e[++tot].to = v;
    e[tot].dist = w;
    e[tot].next = head[u];
    head[u] = tot;
}

int st[maxn][24];

void getST(const int * a, const int n) {
    int m = log(n) / log(2);
    for (int i = 1; i <= n; i++)
        st[i][0] = i;
    for (int j = 1; j <= m; j++)
        for (int i = n; i > 0; i--) {
            if (i + (1 << (j - 1)) > n) continue;
            st[i][j] = (a[st[i][j - 1]] < a[st[i + (1 << (j - 1))][j - 1]]) ?
                st[i][j - 1] : st[i + (1 << (j - 1))][j - 1];
        }
}

int query(int l, int r, const int * a) {
    int k = log(r - l + 1) / log(2);
    return a[st[l][k]] < a[st[r - (1 << k) + 1][k]] ?
        st[l][k] : st[r - (1 << k) + 1][k];
}

int n, m;
int dc; // dfs clock

int vs[maxn * 2], dep[maxn * 2], id[maxn];

void dfs(int u, int fa, int d, int & dc) {
    if (!id[u]) id[u] = dc;
    vs[dc] = u;
    dep[dc++] = d;
    for (int i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].to;
        if (v != fa) {
            dfs(v, u, d + 1, dc);
            vs[dc] = u; // TODO
            dep[dc++] = d;
        }
    }
}

int lca(int u, int v) {
    int l = min(id[u], id[v]);
    int r = max(id[u], id[v]);
    return vs[query(l, r, dep)];
}

void lcainit() {
    tot = 0;
    memset(head, -1, sizeof(head));
    dc = 1;
    memset(dep, inf, sizeof(dep));
    memset(id, 0, sizeof(id));
}

inline void lcaaddedge(int x, int y, int w) {
    addedge(x, y, w);
    addedge(y, x, w);
}

inline void getlca() {
    dfs(1, -1, 0, dc);
    getST(dep, 2 * n);
}

int dist[maxn], vis[maxn];

void dfs(int u, int fa) {
    dist[u] += fa;
    vis[u] = 1;
    for (int i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].to;
        if (vis[v] == 0)
            dfs(v, fa + e[i].dist);
    }
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        lcainit();
        memset(dist, 0, sizeof(dist));
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= m; i++) {
            int t1, t2, t3;
            char t;
            scanf("%d %d %d %c\n", &t1, &t2, &t3, &t);
            lcaaddedge(t1, t2, t3);
        }
        getlca();
        dfs(1, 0);
        int q;
        scanf("%d", &q);
        for (int i = 1; i <= q; i++) {
            int t1, t2;
            scanf("%d%d", &t1, &t2);
            int fa = lca(t1, t2);
            int ans = dist[t1] + dist[t2] - 2 * dist[fa];
            printf("%d\n", ans);
        }
    }
    return 0;
}
