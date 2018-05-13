
#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 100000 + 10000;
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
int din[maxn];
unordered_set<int> sccmultie;

void sccaddedge(int u, int v) {
    sccg[++scctot].to = v;
    sccg[scctot].next = scchead[u];
    scchead[u] = scctot;
    din[v]++;
}

void scc_build(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = head[i]; j != -1; j = e[j].next) {
            int u = i;
            int v = e[j].to;
            if (sccno[v] != sccno[u]) {
                int uu = sccno[u], vv = sccno[v];
                if (sccmultie.find(uu * (n + 1) + vv) != sccmultie.end())
                    continue;
                sccmultie.insert(uu * (n + 1) + vv);
                sccaddedge(uu, vv);
            }
        }
    }
}

void init() {
    sccmultie.clear();
    memset(din, 0, sizeof(din));
    scctot = 0;
    memset(scchead, -1, sizeof(scchead));
    tot = 0;
    memset(head, -1, sizeof(head));
    sc = 0;
    dc = 0;
    memset(sccno, 0, sizeof(sccno));
    memset(dfn, 0, sizeof(dfn));
}

inline int notno(int x, int n) {
    if (x > n)
        return x - n;
    else
        return x + n;
    return -1;
}


struct sat {
    int n; // sum of vars; acctually 2 * n points; 1~n is x, n+1~2n is not x
    int m; // sum of exprs
    bool ans[maxn];
    bool cansolved;
    int sccid[maxn][2];
    int topoorder[maxn];

    vector<pair<int, int> > q; // a U b

    sat() {}

    void satinit() {
        init(); // init of scc graph
        memset(sccid, -1, sizeof(sccid));
        memset(ans, 0, sizeof(ans));
        q.clear();
    }

    void insert(int x, int y) {
        q.push_back(make_pair(x, y));
    }

    void testprint() {
        for (auto i = q.begin(); i != q.end(); i++) {
            printf("%d %d\n", i -> first, i -> second);
        }
    }

    void gettopo() {
        queue<int> q;
        int cnt = 1;
        for (int i = 1; i <= sc; i++)
            if (din[i] == 0)
                q.push(i);
        while (!q.empty()) {
            int f = q.front();
            q.pop();
            topoorder[f] = cnt++;
            for (int j = scchead[f]; ~j; j = sccg[j].next) {
                int v = sccg[j].to;
                din[v]--;
                if (din[v] == 0)
                    q.push(v);
            }
        }
    }

    void solve() {
        /* for (int i = 0; i < q.size(); i++) { */
        for (auto i = q.begin(); i != q.end(); i++) {
            addedge(notno((*i).first, n), (*i).second);
            addedge(notno((*i).second, n), (*i).first);
        }
        for (int i = 1; i <= 2 * n; i++) {
            if (!dfn[i])
                dfs(i);
        }
        for (int i = 1; i <= n; i++)
            sccid[i][0] = sccno[i];
        for (int i = n + 1; i <= 2 * n; i++)
            sccid[i - n][1] = sccno[i];
        for (int i = 1; i <= n; i++) {
            if (sccid[i][0] == sccid[i][1]) {
                if (sccid[i][0] == -1)
                    continue;
                else {
                    cansolved = 0;
                    return;
                }
            }
        }
        cansolved = 1;
        scc_build(2 * n);
        gettopo();
        for (int i = 1; i <= n; i++) {
            if (topoorder[sccid[i][0]] < topoorder[sccid[i][1]])
                ans[i] = 0;
            else
                ans[i] = 1;
        }
    }
};
sat hobo;
int B[maxn];

inline void satSet(sat & x, int i, bool f) {
    if (f) x.insert(i, i);
    if (!f) x.insert(i + x.n, i + x.n);
}

inline bool Equal(int * B, int t1, int x, int t2, int y) {
    return B[t1] == x && B[t2] == y;
}

int main() {
    int t, c = 0;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d%d", &n, &m);
        hobo.satinit();
        hobo.n = n;
        memset(B, 0, sizeof(B));
        for (int i = 1; i <= n; i++)
            scanf("%d", &B[i]);
        for (int i = 1; i <= m; i++) {
            int t1, t2, t3;
            scanf("%d%d%d", &t1, &t2, &t3);
            if (B[t1] == B[t2]) {
                if (t3 == 0) {
                    hobo.insert(t1, t2 + n);
                    hobo.insert(t1 + n, t2);
                }
                else {
                    hobo.insert(t1, t2);
                    hobo.insert(t1 + n, t2 + n);
                }
            }
            else {
                if (t3 == 0) {
                    if (Equal(B, t1, 1, t2, 2) || Equal(B, t1, 3, t2, 1) || Equal(B, t1, 2, t2, 3)) {
                        hobo.insert(t1, t1);
                        hobo.insert(t2 + n, t2 + n);
                    }
                    else {
                        hobo.insert(t1 + n, t1 + n);
                        hobo.insert(t2, t2);
                    }
                }
                else {
                    if (Equal(B, t1, 2, t2, 1) || Equal(B, t1, 1, t2, 3) || Equal(B, t1, 3, t2, 2))
                        hobo.insert(t1, t2 + n);
                    else
                        hobo.insert(t1 + n, t2);
                }
            }
        }
        hobo.solve();
        if (hobo.cansolved)
            printf("Case #%d: yes\n", ++c);
        else
            printf("Case #%d: no\n", ++c);
    }
    return 0;
}
