#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

struct Edge {
    int u, v, cap;
    Edge() {}
    Edge(int u, int v, int cap): u(u), v(v), cap(cap) {}
};

int R, S, T;

const int maxe = 500000; //double of the real edges
const int maxp = 100000 + 50;
const int inf = 0x3f3f3f3f;

Edge es[maxe];
vector<int> tab[maxp];
int dis[maxp], current[maxp];

void init() {
    R = 0;
    memset(es, 0, sizeof(es));
}

void addedge(int u, int v, int cap, int rw = 0) {
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
            if (e.cap > 0 && dis[e.v] == inf) {
                dis[e.v] = dis[h] + 1;
                q.push(e.v);
            }
        }
    }
    return dis[T] < inf;
}

int dinic(int x, int maxflow) {
    if (x == T || maxflow == 0)
        return maxflow;
    for (int i = current[x]; i < tab[x].size(); i++) {
        current[x] = i;
        Edge &e = es[tab[x][i]];
        if (dis[e.v] == dis[x] + 1 && e.cap > 0) {
            int flow = dinic(e.v, min(maxflow, e.cap));
            if (flow) {
                e.cap -= flow;
                es[tab[x][i] ^ 1].cap += flow;
                return flow;
            }
        }
    }
    return 0;
}

int dinic() {
    int ans = 0;
    while (BFS()) {
        int flow;
        memset(current, 0, sizeof(current));
        while (1) {
            flow = dinic(S, 0x3e3e3e3e);
            if (flow == 0) break;
            ans += flow;
        }
    }
    return ans;
}

vector<int> minicut() {
    // dinic();
    vector<int> res;
    res.push_back(S);
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int h = q.front();
        q.pop();
        for (int i = 0; i < tab[h].size(); i++) {
            Edge &e = es[tab[h][i]];
            if (e.cap > 0) {
                res.push_back(e.u);
                q.push(e.v);
            }
        }
    }
    return res;
}

int n, m;
int v[maxp];

long long t;

void read() {
    scanf("%d%d", &n, &m);
    S = n + m + 2;
    T = n + m + 3;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        addedge(i, T, v[i]);
    }
    for (int i = 1; i <= m; i++) {
        int t1, t2, co;
        scanf("%d%d%d", &t1, &t2, &co);
        t += co;
        addedge(i + n, t1, inf);
        addedge(i + n, t2, inf); // TODO
        addedge(S, i + n, co);
    }
}

int solve() {
    return t - dinic();
}

int main() {
    init();
    read();
    printf("%d", solve());

    return 0;
}
