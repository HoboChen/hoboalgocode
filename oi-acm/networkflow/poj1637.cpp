
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>

#define pr(x) cout << #x << " = " << x << endl;

using namespace std;

struct Edge {
    int u, v, cap;
    Edge() {}
    Edge(int u, int v, int cap): u(u), v(v), cap(cap) {}
};

int R, S, T;

const int maxe = 10000; //double of the real edges
const int maxp = 200 + 50;
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
    int a, b, c;
    for (int i = 3; i < n + 3; i++) {
        scanf("%d%d", &a, &b);
        addedge(1, i, a);
        addedge(i, 2, b);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &c);
        addedge(a + 2, b + 2, c, c);
    }
    S = 1;
    T = 2;
    long long ans = dinic();
    cout << ans << endl;
}

const int maxn = 1000;
const int maxm = 5000;

int p[maxn];

int find(int x, int *p) { return p[x] == x ? x : p[x] = find(p[x], p); }

void merge(int i, int j, int *p) {
    int x = find(i, p), y = find(j, p);
    p[y] = x;
}

void init(int * p, int n) {
    for (int i = 1; i <= n; i++)
        p[i] = i;
}

int u[maxn], v[maxn], iss[maxn];
int din[maxn], dout[maxn], delta[maxn];

void debugprint(int n) {
    for (int i = 1; i <= n; i++)
        printf("i = %d, in = %d, out = %d, delta = %d\n",i ,din[i], dout[i], delta[i]);
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        int tm, ts;
        scanf("%d%d", &tm, &ts);
        init(p, tm);
        init();
        memset(din, 0, sizeof(din));
        memset(dout, 0, sizeof(dout));
        memset(delta, 0, sizeof(delta));
        for (int j = 1; j <= ts; j++) {
            scanf("%d%d%d", &u[j], &v[j], &iss[j]);
            dout[u[j]]++;
            din[v[j]]++;
            merge(u[j], v[j], p);
        }
        bool isconnected = 1;
        for (int j = 1; j <= tm; j++) {
            if (find(j, p) != find(1, p)) {
                isconnected = 0;
                break;
            }
        }
        if (!isconnected) {
            /* printf("not connected\n"); */
            printf("impossible\n");
            continue;
        }
        int isodd = 0;
        vector<int> odx;
        for (int j = 1; j <= tm; j++) {
            delta[j] = dout[j] - din[j];
            if (delta[j] % 2 != 0) {
                isodd++;
                odx.push_back(j);
            }
        }
        /* if (isodd != 2 && isodd != 0) */
        if (isodd != 0) {
            /* printf("odd = %d\n", isodd); */
            printf("impossible\n");
            continue;
        }
        /* if (isodd == 2) { */
        /*     din[odx[0]]++; */
        /*     dout[odx[1]]++; */
        /*     delta[odx[0]] = dout[odx[0]] - din[odx[0]]; */
        /*     delta[odx[1]] = dout[odx[1]] - din[odx[1]]; */
        /* } */
        for (int j = 1; j <= ts; j++) {
            if (!iss[j])
                addedge(u[j], v[j], 1);
        }
        S = tm + 1;
        T = tm + 2;
        int outflow = 0;
        for (int j = 1; j <= tm; j++) {
            if (delta[j] == 0) continue;
            if (delta[j] < 0) addedge(j, T, -delta[j] / 2);
            else {
                addedge(S, j, delta[j] / 2);
                outflow += delta[j] / 2;
            }
        }
        long long t = dinic();
        if (t == (long long)outflow) 
            printf("possible\n");
        else 
            printf("impossible\n");
    }
    return 0;
}
