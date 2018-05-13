
#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 1000;
const int maxm = 10000 + 1000;
const double eps = 1e-8;

int a[maxn], n, cnt;
int u[maxm], v[maxm];

struct Edge {
    int u, v;
    double cap;
    Edge() {}
    Edge(int u, int v, double cap): u(u), v(v), cap(cap) {}
};

int R, S, T;

const int maxe = 10000 + 1000; //double of the real edges
const int maxp = 10000 + 1000;
const int inf = 0x3f3f3f3f;

Edge es[maxe];
vector<int> tab[maxp];
int dis[maxp], current[maxp];

void init() {
    R = 0;
    for (int i = 0; i < maxp; i++)
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
        for (int i = 0; i < (int)tab[h].size(); i++) {
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
    for (int i = current[x]; i < (int)tab[x].size(); i++) {
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

void buildgraph(double x) {
    init();
    int m = cnt;
    S = n + m + 2;
    T = n + m + 3;
    for (int i = 0; i < cnt; i++) {
        addedge(n + 1 + i, u[i], inf);
        addedge(n + 1 + i, v[i], inf);
        addedge(S, n + 1 + i, 1);
    }
    for (int i = 0; i < n; i++)
        addedge(i + 1, T, x);
}

double solve() {
    cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j])
                u[cnt] = a[i], v[cnt++] = a[j]; // TODO
    init();
    int m = cnt;
    S = n + m + 2;
    T = n + m + 3;
    for (int i = 0; i < cnt; i++) {
        addedge(n + 1 + i, u[i], inf);
        addedge(n + 1 + i, v[i], inf);
        addedge(S, n + 1 + i, 1);
    }
    for (int i = 0; i < n; i++)
        addedge(i + 1, T, 10);
    double l = 0, r = cnt + 1, mid = (l + r) / 2;
    while (r - l > eps) {
        mid = (l + r) / 2;
        buildgraph(mid);
        bool f = cnt - dinic() > 0;
        if (f)
            l = mid;
        else
            r= mid;
    }
    return mid;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        scanf("%d", &n);
        for (int j = 0; j < n; j++)
            scanf("%d", &a[j]);
        printf("Case #%d: %.6lf\n", i, solve());
    }
    return 0;
}
