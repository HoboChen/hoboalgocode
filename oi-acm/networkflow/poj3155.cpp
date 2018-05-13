#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>


using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 1000;
const int maxm = 2000;
const double eps = 1e-6;

const int MAXN = 2000;
const int MAXM = 5000;
const int INF = 0x3f3f3f3f;

int a[maxn], n, cnt;
int u[maxm], v[maxm];

struct Edge {
    int from, to, next;
    double cap;
    double flow;
    void c(int ff, int t, int n, double c, double f) {
        from = ff;
        to = t;
        next = n;
        cap = c;
        flow = f;
    }
}edge[MAXM];

int tol, head[MAXN], gap[MAXN], dep[MAXN], cur[MAXN];

void init() {
    tol = 0;
    memset(head, -1, sizeof(head));
}

void addedge(int u, int v, double w, double rw = 0) {
    edge[tol].c(u, v, head[u], w, 0);
    head[u] = tol++;
    edge[tol].c(v, u, head[v], rw, 0);
    head[v] = tol++;
}

int Q[MAXN];

void BFS(int start, int end) {
    memset(dep, -1, sizeof(dep));
    memset(gap, 0, sizeof(gap));
    gap[0] = 1;
    int front = 0, rear = 0;
    dep[end] = 0;
    Q[rear++] = end;
    while(front != rear) {
        int u = Q[front++];
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if (dep[v] != -1) continue;
            Q[rear++] = v;
            dep[v] = dep[u] + 1;
            gap[dep[v]]++;
        }
    }
}

int S[MAXN];

double isap(int start, int end, int N) {
    BFS(start, end);
    memcpy(cur, head, sizeof(head));
    int top = 0, u = start;
    double ans = 0;
    while (dep[start] < N) {
        if (u == end) {
            double Min = INF;
            int inser;
            for (int i = 0;i < top;i++)
                if(Min > edge[S[i]].cap - edge[S[i]].flow) {
                    Min = edge[S[i]].cap - edge[S[i]].flow;
                    inser = i;
                }
            for (int i = 0;i < top;i++) {
                edge[S[i]].flow += Min;
                edge[S[i]^1].flow -= Min;
            }
            ans += Min;
            top = inser;
            u = edge[S[top]^1].to;
            continue;
        }
        bool flag = false;
        int v;
        for (int i = cur[u]; i != -1; i = edge[i].next) {
            v = edge[i].to;
            if (edge[i].cap - edge[i].flow > eps && dep[v] + 1 == dep[u]) {
                flag = true;
                cur[u] = i;
                break;
            }
        }
        if (flag) {
            S[top++] = cur[u];
            u = v;
            continue;
        }
        int Min = N;
        for(int i = head[u]; i != -1; i = edge[i].next)
            if(edge[i].cap - edge[i].flow > eps && dep[edge[i].to] < Min) {
                Min = dep[edge[i].to];
                cur[u] = i;
            }
        gap[dep[u]]--;
        if (!gap[dep[u]]) return ans;
        dep[u] = Min + 1;
        gap[dep[u]]++;
        if(u != start) u = edge[S[--top]^1].to;
    }
    return ans;
}

const int inf = 0x3e3e3e3e;

int dnode[maxn];

double buildgraph(double x = 10) {
    init();
    memset(dnode, 0, sizeof(dnode));
    int m = cnt;
    int S = n + 1;
    int T = n + 2;
    for (int i = 0; i < m; i++) {
        addedge(u[i], v[i], 1);
        addedge(v[i], u[i], 1);
        dnode[u[i]]++;
        dnode[v[i]]++;
    }
    double U = cnt + 1;
    for (int i = 1; i <= n; i++) {
        addedge(S, i, U);
    }
    for (int i = 1; i <= n; i++) {

        addedge(i, T, U + 2 * x - dnode[i]);
    }
    return U;
}

void rebuildgraph(double x, double U) {
    for (int i = 1; i <= n + 2; i++)
        for (int j = head[i]; ~j; j = edge[j].next) {
            edge[j].flow = 0;
            if (edge[j].to == n + 2)
                edge[j].cap = U + 2 * x - dnode[i];
        }
}

int color[maxn];

void getcutT(int u) {
    if (color[u]) return;
    color[u] = 1;
    for (int i = head[u]; ~i; i = edge[i].next) {
        int nu = i - 1;
        if ((edge[nu].cap - edge[nu].flow) > eps && edge[nu].cap > 0) {
            int v = edge[nu].from;
            getcutT(v);
        }
    }
}

int anssum;

void getcutS(int u) {
    if (color[u]) return;
    color[u] = 1;
    anssum++;
    for (int i = head[u]; ~i; i = edge[i].next) {
        if (edge[i].cap - edge[i].flow > 0 && edge[i].cap >= 0) {
            int v = edge[i].to;
            getcutS(v);
        }
    }
}

double solve() {
    anssum = 0;
    memset(color, 0, sizeof(color));
    double U = buildgraph(10);
    double l = 0, r = cnt + 1, mid;
    while (r - l > eps) {
        mid = (l + r) / 2.0;
        rebuildgraph(mid, U);
        double flow = isap(n + 1, n + 2, n + 2);
        bool f = (U * n - flow) / 2.0 > eps;
        if (f)
            l = mid;
        else
            r = mid;
    }
    rebuildgraph(l, U);
    double flow = isap(n + 1, n + 2, n + 2);
    getcutS(n + 1);
    // getcutT(n + 2); // you will get WA in 2 of 60 test cases, and i dont know why
    return mid;
}

int m;

int main() {
    while (scanf("%d%d", &n, &m) == 2) {    
        for (int i = 0; i < m; i++)
            scanf("%d%d", &u[i], &v[i]);
        cnt = m;
        double tmp = solve();
        if (tmp < eps) {
            printf("%d\n%d", 1, 1);
            continue;
        }
        else {
            printf("%d\n", anssum - 1);
            for (int i = 1; i <= n; i++)
                if (color[i])
                    printf("%d\n", i);
        }
    }
    return 0;
}

