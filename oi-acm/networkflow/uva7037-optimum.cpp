// 600 ms
#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 1000;
const int maxm = 10000 + 1000;
const double eps = 1e-7;

const int MAXN = 10000 + 1000;
const int MAXM = 20000 + 10000;
const int INF = 0x3f3f3f3f;

int a[maxn], n, cnt;
int u[maxm], v[maxm];

struct Edge {
    int to, next;
    double cap;
    double flow;
    void c(int t, int n, double c, double f) {
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
    edge[tol].c(v, head[u], w, 0);
    head[u] = tol++;
    edge[tol].c(u, head[v], rw, 0);
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
        addedge(u[i], v[i], 1, 1);
        dnode[u[i]]++;
        dnode[v[i]]++;
    }
    double U = cnt + 1;
    for (int i = 1; i <= n; i++)
        addedge(S, i, U);
    for (int i = 1; i <= n; i++)
        addedge(i, T, U + 2 * x - dnode[i]);
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

double solve() {
    cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j])
                u[cnt] = a[i], v[cnt++] = a[j];
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
