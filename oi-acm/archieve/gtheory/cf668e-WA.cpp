
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define fio 0
#else
#define fio 1
#endif

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

inline void px(string s) { cout << s << ends; }

const int maxn = 200000 + 10000;
const int maxm = 400000 + 10000;
const double eps = 1e-10;

struct edge { int to, next; };
struct scc {
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
        /* pr(u) pr(v) pn; */
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
};

inline int notno(int x, int n) {
    if (x > n)
        return x - n;
    else
        return x + n;
    return -1;
}


struct sat {
    scc satscc;
    int n; // sum of vars; acctually 2 * n points; 1~n is x, n+1~2n is not x
    int m; // sum of exprs
    bool ans[maxn], isfree[maxn], cansolved;
    int sccid[maxn][2], topoorder[maxn], color[maxn], colorcnt;

    edge edgecolor[maxm];
    int colorhead[maxn], colortot;

    vector<pair<int, int> > q; // a U b

    sat() {}

    void colorinit() {
        memset(color, -1, sizeof(color));
        memset(colorhead, -1, sizeof(colorhead)); 
        colortot = 0;
        colorcnt = 0;
    }

    void coloraddedge(int u, int v) {
        edgecolor[++colortot].to = v;
        edgecolor[colortot].next = colorhead[u];
        colorhead[u] = colortot;
    }

    void colordfs(int x, int fa) {
        /* pr(x) pr(fa) pn */
        if (fa == -1)
            color[x] = ++colorcnt;
        else 
            color[x] = colorcnt;
        for (int i = colorhead[x]; ~i; i = edgecolor[i].next) {
            int v = edgecolor[i].to;
            if (color[v] == -1)
                colordfs(v, x);
        }
    }
    
    void getcolor() {
         for (auto i = satscc.sccmultie.begin(); i != satscc.sccmultie.end(); i++) {
             int e = *i;
             int u = e / (2 * n + 1);
             int v = e % (2 * n + 1);
             /* cout << "coloredge"; pr(u) pr(v) pn */
             coloraddedge(u, v);
             coloraddedge(v, u);
         }
         for (int i = 1; i <= satscc.sc; i++) {
             if (color[i] == -1) {
                 colordfs(i, -1);
             }
         }
    }

    void satinit() {
        satscc.init(); // init of scc graph
        colorinit(); // if want color
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
        for (int i = 1; i <= satscc.sc; i++)
            if (satscc.din[i] == 0)
                q.push(i);
        while (!q.empty()) {
            int f = q.front();
            q.pop();
            topoorder[f] = cnt++;
            for (int j = satscc.scchead[f]; ~j; j = satscc.sccg[j].next) {
                int v = satscc.sccg[j].to;
                satscc.din[v]--;
                if (satscc.din[v] == 0)
                    q.push(v);
            }
        }
    }

    
    void solve() {
        for (int i = 0; i < q.size(); i++) {
            satscc.addedge(notno(q[i].first, n), q[i].second);
            satscc.addedge(notno(q[i].second, n), q[i].first);
        }
        for (int i = 1; i <= 2 * n; i++) {
            if (!satscc.dfn[i])
                satscc.dfs(i);
        }
        for (int i = 1; i <= n; i++) sccid[i][0] = satscc.sccno[i];
        for (int i = n + 1; i <= 2 * n; i++) sccid[i - n][1] = satscc.sccno[i];
        for (int i = 1; i <= n; i++) {
            if (sccid[i][0] == sccid[i][1]) {
                if (sccid[i][0] == -1) continue;
                else { cansolved = 0; return; }
            }
        }
        cansolved = 1;
        satscc.scc_build(2 * n);
        gettopo();
        getcolor(); 
        for (int i = 1; i <= n; i++) {
            if (topoorder[sccid[i][0]] < topoorder[sccid[i][1]]) ans[i] = 0;
            else ans[i] = 1;
            if (color[sccid[i][0]] != color[sccid[i][1]]) 
                isfree[i] = 1;
            else 
                isfree[i] = 0;
        }
    }
};

sat hobo, eddie;

void testprint(sat & x) {
    /* printf("SCCID\n"); */
    /* for (int i = 1; i <= x.n; i++) { */
    /*     printf("sccid: %d %d\n", x.sccid[i][0], x.sccid[i][1]); */
    /* } */
    /* printf("TOPOODER\n"); */
    /* for (int i = 1; i <= x.n; i++) */ 
    /*     printf("topoorder of sccid: %d %d\n", x.topoorder[x.sccid[i][0]], x.topoorder[x.sccid[i][1]]); */
    /* printf("COLOR\n"); */
    /* for (int i = 1; i <= x.n; i++) { */
    /*     printf("color of sccid: %d %d\n", x.color[x.sccid[i][0]], x.color[x.sccid[i][1]]); */
    /* } */
    /* printf("IS FREE\n"); */
    for (int i = 1; i <= x.n; i++) 
        printf("%d ", x.isfree[i]);
    /* printf("END\n"); */
}

int main() {
    if (fio) freopen("in", "r", stdin);
    int n, m1, m2;
    scanf("%d%d%d", &n, &m1, &m2);
    hobo.satinit();
    eddie.satinit();
    hobo.n = n;
    eddie.n = n;
    for (int i = 0; i < m1; i++) {
        int t1, t2;
        scanf("%d%d", &t1, &t2);
        if (t1 < 0) t1 += 2 * n;
        if (t2 < 0) t2 += 2 * n;
        hobo.insert(t1, t2);
    }
    for (int i = 0; i < m2; i++) {
        int t1, t2;
        scanf("%d%d", &t1, &t2);
        if (t1 < 0) t1 += 2 * n;
        if (t2 < 0) t2 += 2 * n;
        eddie.insert(t1, t2);
    }
    hobo.solve();
    eddie.solve();
    testprint(hobo);
    /* testprint(eddie); */
    if (hobo.cansolved == 0 || eddie.cansolved == 0) {
        printf("input error\n");
        return 0;
    }
    bool res = 1;
    for (int i = 1; i <= n; i++) {
        if (hobo.isfree[i] == 1 && eddie.isfree[i] == 1)
            continue;
        else if (hobo.isfree[i] == 0 && eddie.isfree[i] == 0 && hobo.ans[i] == eddie.ans[i])
            continue;
        else res = 0;
    }
    if (res) {
        printf("SIMILAR\n");
        return 0;
    }
    else {
        for (int i = 1; i <= n; i++) {
            if (hobo.isfree[i] == 0 && eddie.isfree[i] == 0) {
                printf("%d ", hobo.ans[i]);
            }
            if (hobo.isfree[i] == 1 && eddie.isfree[i] == 1) {
                printf("%d ", hobo.ans[i]);
            }
            if (hobo.isfree[i] == 1 && eddie.isfree[i] == 0) {
                printf("%d ", (eddie.ans[i] + 1) % 2);
            }
            if (hobo.isfree[i] == 0 && eddie.isfree[i] == 1) {
                printf("%d ", (hobo.ans[i] + 1) % 2);
            }
        }
    }
    return 0;
}
