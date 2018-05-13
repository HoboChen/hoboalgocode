#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 20000 + 1000;
const int maxm = 100000 + 10000;
const int inf = 0x3e3e3e3e;
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
xint low[maxn]; // the first node connected by non-fa-son edge 
bool vis[maxn];

set<int> ansp;
set<pair<int, int> > anse;

int sc; // dfs clock

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

int ebcc;
int ebccno[maxn];

void ebcc_dfs(int u, int fa) {
    if (fa == -1) 
        ebccno[u] = ++ebcc;
    else
        ebccno[u] = ebcc;
    vis[u] = 0;
    for (int i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].to;
        if (anse.find(make_pair(min(u, v), max(u, v))) != anse.end())
            continue;
        if (vis[v])
            ebcc_dfs(v, u);
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
        // find bridge
        for (int i = 1; i <= n; i++) 
            if (vis[i])
                dfs(i);
        // find e-bcc
        memset(vis, 1, sizeof(vis));
        ebcc = 0;
        for (int i = 1; i <= n; i++) {
            if (vis[i]) 
                ebcc_dfs(i, -1);
        }
        // get ans
        vector<int> ebcc_set[maxn];
        int *bccminno = new int[maxn];
        memset(bccminno, inf, maxn * sizeof(int));
        for (int i = 1; i <= n; i++)
            ebcc_set[ebccno[i]].push_back(i);
        map<int, int> ans;
        for (int i = 1; i <= ebcc; i++) {
            int m = *(min_element(ebcc_set[i].begin(), ebcc_set[i].end()));
            for (auto j = ebcc_set[i].begin(); j != ebcc_set[i].end(); j++)
                ans[*j] = m;
        }
        printf("%d\n", ebcc);
        for (int i = 1; i <= n; i++) 
            printf("%d ", ans[i]);
        pn
    }
    return 0;
}

