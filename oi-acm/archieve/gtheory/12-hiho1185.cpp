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

int dfn[maxn], lowlink[maxn], sccno[maxn], sc, dc;

stack<int> s;

void dfs(int u) {
    dfn[u] = lowlink[u] = ++dc;
    s.push(u);
    for (int i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].to;
        if (!dfn[v]) {
            dfs(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
        }
        else if (!sccno[v])
            lowlink[u] = min(lowlink[u], dfn[v]);
    }
    if (lowlink[u] == dfn[u]) {
        sc++;
        for (;;) {
            int x = s.top();
            s.pop();
            sccno[x] = sc;
            if (x == u) break;
        }
    }
}

edge sccg[maxm];
int scchead[maxn];
int scctot;

void sccaddedge(int u, int v) {
    sccg[++scctot].to = v;
    sccg[scctot].next = scchead[u];
    scchead[u] = scctot;
}

void scc_build(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = head[i]; j != -1; j = e[j].next) {
            int u = i;
            int v = e[j].to;
            if (sccno[v] != sccno[u])
                sccaddedge(sccno[u], sccno[v]);
        }
    }
}

int val[maxn]; // this prob
long long sccv[maxn];

long long f[maxn];

long long DAG_DP(int u) {
    if (f[u] >= 0)
        return f[u];
    f[u] = sccv[u];
    for (int i = scchead[u]; i != -1; i = sccg[i].next) {
        int v = sccg[i].to;
        f[u] = max(f[u], DAG_DP(v) + sccv[u]);
    }
    return f[u];
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2 && n && m) {
        tot = 0;
        memset(head, -1, sizeof(head));
        sc = 0; // scc count
        dc = 0; // dfs clock
        memset(sccno, 0, sizeof(sccno));
        memset(dfn, 0, sizeof(dfn));
        for (int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
        }
        for (int i = 0; i < m; i++) {
            int t1, t2;
            scanf("%d%d", &t1, &t2);
            addedge(t1, t2);
        }
        // find scc
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                dfs(i);
            }
        }
        scctot = 0;
        memset(scchead, -1, sizeof(scchead));
        memset(sccv, 0, sizeof(sccv));
        memset(f, -1, sizeof(f));
        // rebuild scc graph
        scc_build(n);
        for (int i = 1; i <= n; i++)
            sccv[sccno[i]] += val[i];
        cout << DAG_DP(sccno[1]) << endl;
    }
    return 0;
}
