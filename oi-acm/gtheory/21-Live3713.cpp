#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 200000 + 10000;
const int maxm = 400000 + 10000;
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
        for (int i = 0; i < q.size(); i++) {
            addedge(notno(q[i].first, n), q[i].second);
            addedge(notno(q[i].second, n), q[i].first);
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

bool isold[maxn];
int age[maxn];
char res[maxn];

int uu[maxm], vv[maxm];

int main() {
    int n, m; 
    while (scanf("%d%d", &n, &m) == 2) {
        hobo.satinit();
        hobo.n = n;
        if (n == 0 && m == 0) break;
        long long sumage = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &age[i]);
            sumage += age[i];
        }
        for (int i = 1; i <= n; i++) {
            if (age[i] * n >= sumage)
                isold[i] = 1;
            else 
                isold[i] = 0;
        }
        for (int i = 1; i <= m; i++) {
            int t1, t2;
            scanf("%d%d", &t1, &t2);
            uu[i] = t1;
            vv[i] = t2;
            hobo.insert(t1, t2);
            if (isold[t1] == isold[t2])
                hobo.insert(t1 + n, t2 + n);
        }
        hobo.solve();
        if (!hobo.cansolved) {
            printf("No solution.\n");
            continue;
        }
        else {
            for (int i = 1; i <= n; i++) {
                if (hobo.ans[i]) {
                    if (isold[i]) res[i] = 'A';
                    else res[i] = 'B'; 
                }
                else res[i] = 'C'; 
            }
        }
        for (int i = 1; i <= n; i++) 
            printf("%c\n", res[i]);
    }            
    return 0;
}
