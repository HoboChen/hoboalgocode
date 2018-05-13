// poj2195, 110ms, 1140kb
// spfa, nm^2, point starts at 0

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn = 500;
const int maxm = 20000 + 10000;
const int inf = 0x3f3f3f3f;

struct Edge {
    int to, next, cap, flow, cost;
    void c(int t, int c, int co, int f, int n) {
        to = t;
        cap = c;
        cost = co;
        flow = f;
        next = n;
    }
}edge[maxm];

int head[maxn], tol, pre[maxn], dis[maxn], N;
bool vis[maxn];

void init(int n) {
    N = n;
    tol = 0;
    memset(head, -1, sizeof(head));
}

void addedge(int u, int v, int cap, int cost) {
    edge[tol].c(v, cap, cost, 0, head[u]);
    head[u] = tol++;
    edge[tol].c(u, 0, -cost, 0, head[v]);
    head[v] = tol++;
}

bool spfa(int s,int t) {
    queue<int> q;
    for(int i = 0; i < N; i++) {
        dis[i] = inf;
        vis[i] = false;
        pre[i] = -1;
    }
    dis[s] = 0;
    vis[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if(edge[i].cap > edge[i].flow &&
                    dis[v] > dis[u] + edge[i].cost ) {
                dis[v] = dis[u] + edge[i].cost;
                pre[v] = i;
                if(!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    if(pre[t] == -1) return false;
    else return true;
}

int mincostmaxflow(int s, int t, int &cost)
{
    int flow = 0;
    cost = 0;
    while (spfa(s,t)) {
        int Min = inf;
        for(int i = pre[t]; i != -1; i = pre[edge[i^1].to]) {
            if(Min > edge[i].cap - edge[i].flow)
                Min = edge[i].cap - edge[i].flow;
        }
        for(int i = pre[t]; i != -1; i = pre[edge[i^1].to]) {
            edge[i].flow += Min;
            edge[i^1].flow -= Min;
            cost += edge[i].cost * Min;
        }
        flow += Min;
    }
    return flow;
}

int n, m;

inline bool v(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};


inline int manhatten(vector<pair<int, int> >& t, int i,
        vector<pair<int, int> >& s, int j) {
    return abs(t[i].first - s[j].first) + abs(t[i].second - s[j].second);
}

void solve() {
    char ma[105][105];
    while (~scanf("%d%d", &n, &m) && (n && m)) {
        vector<pair<int, int> > humbn;
        vector<pair<int, int> > hoube;
        init(408);
        memset(ma, 0, sizeof(ma));
        string ma[100];
        for (int i = 0; i < n; i++) {
            cin >> ma[i];
            for (int j = 0; j < ma[i].length(); j++) {
                if (ma[i][j] == 'H')
                    hoube.push_back(make_pair(i, j));
                if (ma[i][j] == 'm')
                    humbn.push_back(make_pair(i, j));
            }
        }
        for (int i = 0; i < humbn.size(); i++) {
            addedge(405, i, 1, 0);
            for (int j = 0; j < hoube.size(); j++)
                addedge(i, j + 100, 1, manhatten(humbn, i, hoube, j));
        }
        for (int j = 0; j < hoube.size(); j++)
            addedge(j + 100, 407, 1, 0);
        int res;
        int f = mincostmaxflow(405, 407, res);
        printf("%d\n", res);
    }
}

int main() {
    solve();
    return 0;
}
