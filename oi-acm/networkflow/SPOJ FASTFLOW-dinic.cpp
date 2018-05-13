
// poj3469, 5688ms, 10332kb
// dinic, n^3, point starts at 0

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
const int maxp = 20000 + 50;
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

long long dinic(int x, long long maxflow) {
    if (x == T || maxflow == 0)
        return maxflow;
    for (int i = current[x]; i < tab[x].size(); i++) {
        current[x] = i;
        Edge &e = es[tab[x][i]];
        if (dis[e.v] == dis[x] + 1 && e.cap > 0) {
            int flow = dinic(e.v, min(maxflow, (long long)e.cap));
            if (flow) {
                e.cap -= flow;
                es[tab[x][i] ^ 1].cap += flow;
                return flow;
            }
        }
    }
    return 0;
}

const long long llinf = (long long)0x3e3e3e3e * 0x3e3e3e3e;

long long dinic() {
    long long ans = 0;
    while (BFS()) {
        long long flow;
        memset(current, 0, sizeof(current));
        while (1) {
            flow = dinic(S, llinf);
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


void solve() {
    init();
    int n, m;
    scanf("%d%d", &n, &m);
    S = 1;
    T = n;
    for (int i = 0; i < m; i++) {
        int t1, t2, t3;
        scanf("%d%d%d", &t1, &t2, &t3);
        addedge(t1, t2, t3, t3);
    }

    long long ans = dinic();
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}
