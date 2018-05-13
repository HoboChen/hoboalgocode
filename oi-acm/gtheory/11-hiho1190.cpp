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

int dfn[maxn], bccno[maxn];
bool iscut[maxn], vis[maxn];

int bc; // bcc count
int sc; // dfs clock

stack<pair<int, int> > s;
vector<int> bcc[maxn];

vector<int> t[maxm];
unordered_map<int, int> edgeno;
int bccedgeno[maxm];

int dfs(int u, int fa) {
    vis[u] = 0;
    int ch = 0;
    int lowu = dfn[u] = ++sc;
    for (int i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].to;
        pair<int, int> e = make_pair(u, v);
        if (vis[v]) {
            s.push(e);
            ch++;
            vis[v] = 0;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if (lowv >= dfn[u]) {
                iscut[u] = 1;
                bcc[++bc].clear(); // starts from 1
                t[bc].clear();
                for (;;) {
                    pair<int, int> x = s.top();
                    s.pop();
                    int mi = min(x.first, x.second);
                    int ma = max(x.first, x.second);
                    int tmp = mi * maxn + ma; 
                    t[bc].push_back(edgeno[tmp]);
                    bccedgeno[edgeno[tmp]] = bc;
                    if (bccno[x.first] != bc) {
                        bcc[bc].push_back(x.first);
                        bccno[x.first] = bc;
                    }
                    if (bccno[x.second] != bc) {
                        bcc[bc].push_back(x.second);
                        bccno[x.second] = bc;
                    }
                    if (x.first == u && x.second == v) 
                        break;
                }
            }
        }
        else if (dfn[v] < dfn[u] && v != fa) {
            s.push(e);
            lowu = min(lowu, dfn[v]);
        }
    }
    if (fa < 0 && ch == 1)
        iscut[u] = 0;
    return lowu;
}


int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2 && n &&m ) {
        tot = 0;
        memset(head, -1, sizeof(head));
        memset(dfn, 0, sizeof(dfn));
        memset(iscut, 0, sizeof(iscut));
        memset(bccno, 0, sizeof(bccno));
        memset(vis, 1, sizeof(vis));
        bc = sc = 0;
        edgeno.clear();
        for (int i = 0; i < m; i++) {
            int t1, t2;
            scanf("%d%d", &t1, &t2);
            addedge(t1, t2);
            addedge(t2, t1);
            int mi = min(t1, t2);
            int ma = max(t1, t2);
            edgeno[mi * maxn + ma] = i + 1;
        }
        for (int i = 1; i <= n; i++)
            if (vis[i]) 
                dfs(i, -1);
        map<int, int> ans;
        printf("%d\n", bc);
        for (int i = 1; i <= bc; i++) {
            ans[i] = *min_element(t[i].begin(), t[i].end());
        }
        for (int i = 1; i <= m; i++)
            printf("%d ", ans[bccedgeno[i]]);
        printf("\n");
    }
    return 0;
}

