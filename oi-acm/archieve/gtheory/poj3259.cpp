#include <iostream>
#include <cstring>
#include <stack>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <deque>
#include <bitset>
#include <algorithm>

using namespace std;

const int maxn = 500 + 5;
const int maxm = 10000 + 5;
const double eps = 1e-10;
const int INF = 0x3e3e3e3e;

struct edge {
    int to, next, dist;
};

edge e[maxm];
int head[maxn];
int tot;

void addedge(int u, int v, int w) {
    e[++tot].to = v;
    e[tot].dist = w;
    e[tot].next = head[u];
    head[u] = tot;
}

void init() {
    tot = 0;
    memset(head, -1, sizeof(head));
}

int d[maxn];
//if exist negative circle return true
bool spfa(int S, int n) {
    int cnt[maxn];
    bool inq[maxn];
    queue<int> Q;
    memset(inq, 0, sizeof(inq));
    memset(cnt, 0, sizeof(cnt));
    //1. judge whether negative circle exist in the graph, the graph may be not linked
    for (int i = 1; i <= n; i++) {
        d[i] = 0;
        Q.push(i);
    }
    //2. calculate the distance from start
    //for (int i = 1; i <= n; i++) d[i] = INF;
    //Q.push(S);
    inq[S] = 1; d[S] = 0;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        inq[u] = false;
        for (int i = head[u]; ~i; i = e[i].next) {
            edge ed = e[i];
            if (d[ed.to] > d[u] + ed.dist) {
                d[ed.to] = d[u] + ed.dist;
                if (!inq[ed.to]) {
                    Q.push(ed.to);
                    inq[ed.to] = 1;
                    if (++cnt[ed.to] > n) return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, w;
        init();
        scanf("%d%d%d", &n, &m, &w);
        int x, y, z;
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &x, &y, &z);
            addedge(x, y, z);
            addedge(y, x, z);
        }
        for (int i = 0; i < w; i++) {
            scanf("%d%d%d", &x, &y, &z);
            addedge(x, y, -z);
        }
        if (spfa(1, n)) puts("YES");
        else puts("NO");
    }
    return 0;
}

