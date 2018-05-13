
#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 20000 + 1000;
const int maxm = 100000 + 10000;
const double eps = 1e-10;

struct edge { int to, next; };
edge e[maxm];
int head[maxn];
int tot;

void addedge(int u, int v) {
    e[++tot].to = v;
    e[tot].next = head[u];
    head[u] = tot;
}

int pa[maxn]; // parent idx
int dfn[maxn]; // the number of dfs sequence
int low[maxn]; // the first node connected by non-fa-son edge
bool vis[maxn];

set<int> ansp;
set<pair<int, int> > anse;

int sc;

void dfs(int u) {
    int ch = 0;
    dfn[u] = low[u] = ++sc;
    vis[u] = 0;
    for (int i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].to;
        if (vis[v]) {
            vis[v] = 0;
            ch++;
            pa[v] = u;
            dfs(v);
            low[u] = min(low[u], low[v]);
            if (pa[u] == -1 && ch > 1) // rule no.1
                ansp.insert(u); // may many times
            if (pa[u] != -1 && low[v] >= dfn[u]) // rule no.2
                ansp.insert(u); // may many times
            if (low[v] > dfn[u])
                anse.insert(make_pair(min(u, v), max(u, v)));
        }
        else if (v != pa[u]) // non fa-son && non tree edge
            low[u] = min(low[u], dfn[v]);
    }
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2 && n && m) {
        sc = 0;
        tot = 0;
        memset(head, -1, sizeof(head));
        memset(pa, -1, sizeof(pa));
        memset(vis, 1, sizeof(vis));
        ansp.clear();
        anse.clear();
        for (int i = 0; i < m; i++) {
            int t1, t2;
            scanf("%d%d", &t1, &t2);
            addedge(t1, t2);
            addedge(t2, t1);
        }
        for (int i = 1; i <= n; i++)
            if (vis[i])
                dfs(i);
        if (ansp.size() == 0) {
            printf("Null\n");
            continue;
        }
        for (auto i = ansp.begin(); i != ansp.end(); i++)
            printf("%d ", *i);
        printf("\n");
        if (anse.size() == 0) continue;
        for (auto i = anse.begin(); i != anse.end(); i++) {
            printf("%d %d\n", i -> first, i -> second);
        }
    }
    return 0;
}
