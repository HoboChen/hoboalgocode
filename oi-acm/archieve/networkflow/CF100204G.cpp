
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

#define pr(x) cout << #x << " = " << x << " $ ";
#define pn cout << endl; 

struct Edge {
    int u, v;
    double cap;
    Edge() {}
    Edge(int u, int v, double cap): u(u), v(v), cap(cap) {}
};

int R, S, T;

const int maxe = 2000; //double of the real edges
const int maxp = 500;
const int inf = 0x3f3f3f3f;

Edge es[maxe];
vector<int> tab[maxp];
int dis[maxp], current[maxp];
const double eps = 1e-8;

int n, m;

void init() {
    R = 0;
    for (int i = 0; i < n + 1; i++)
        tab[i].clear();
    memset(es, 0, sizeof(es));
}

void addedge(int u, int v, double cap, double rw = 0) {
    tab[u].push_back(R);
    es[R++] = Edge(u, v, cap);
    tab[v].push_back(R);
    es[R++] = Edge(v, u, rw);
}

int BFS() {
    queue<int> q;
    q.push(S);
    memset(dis, 0x3f, sizeof(dis));
    dis[S] = 0;
    while (!q.empty()) {
        int h = q.front();
        q.pop();
        for (int i = 0; i < tab[h].size(); i++) {
            Edge &e = es[tab[h][i]];
            if (e.cap > eps && dis[e.v] == inf) {
                dis[e.v] = dis[h] + 1;
                q.push(e.v);
            }
        }
    }
    return dis[T] < inf;
}

double dinic(int x, double maxflow) {
    if (x == T || maxflow < eps)
        return maxflow;
    for (int i = current[x]; i < tab[x].size(); i++) {
        current[x] = i;
        Edge &e = es[tab[x][i]];
        if (dis[e.v] == dis[x] + 1 && e.cap > eps) {
            double flow = dinic(e.v, fmin(maxflow, e.cap));
            if (flow) {
                e.cap -= flow;
                es[tab[x][i] ^ 1].cap += flow;
                return flow;
            }
        }
    }
    return 0;
}

double dinic() {
    double ans = 0;
    while (BFS()) {
        double flow;
        memset(current, 0, sizeof(current));
        while (1) {
            flow = dinic(S, 0x3e3e3e3e);
            if (flow < eps) break;
            ans += flow;
        }
    }
    return ans;
}

int u[maxe], v[maxe], color[maxe];
double cc[maxe];

void debugprint() {
    for (int i = 0; i < R; i++) {
        pr(es[i].u) pr(es[i].v) pr(es[i].cap) pn
    }
}


bool check(double x) {
    init();
	S = 1;
	T = n;
    double ret = 0;
    for (int i = 0; i < m; i++) {
        double t = cc[i] - x;
        if (t > 0) {
            addedge(u[i], v[i], cc[i] - x);
            addedge(v[i], u[i], cc[i] - x);
        }
        else ret += t;
    }
    double f = dinic();
    ret += f;
    return ret > 0;
}

void dfs(int x) {
    if (color[x]) return;
    color[x] = 1;
    for (int i = 0; i < tab[x].size(); i++)
        if (es[tab[x][i]].cap > eps) {
            int v = es[tab[x][i]].v;
            dfs(v);
        }
}

void solve() {
    memset(color, 0, sizeof(color));
    for (int i = 0; i < m; i++) {
        scanf("%d%d%lf", &u[i], &v[i], &cc[i]);
	}
    double l = 0, r = 1e10;
    double mid = (l + r) / 2;
    while (r - l > eps) {
        mid = (l + r) / 2;
        if (check(mid)) 
            l = mid;
        else
            r = mid;
    }
    check(mid); 
    vector<int> ret;
    dfs(S);
    for (int i = 0; i < m; i++) {
        if (cc[i] - mid < eps)
            ret.push_back(i + 1);
        else if (color[u[i]] ^ color[v[i]]) 
            ret.push_back(i + 1);
    }
    printf("%d\n", (int)ret.size());
    for (int i = 0; i < ret.size(); i++) {
        if (i) printf(" %d", ret[i]);
        else printf("%d", ret[i]);
    }
    printf("\n");
}

int main() {
    freopen("network.in", "r", stdin);
    freopen("network.out", "w", stdout);
    while (scanf("%d%d", &n, &m) == 2) 
        solve();
    return 0;
}
