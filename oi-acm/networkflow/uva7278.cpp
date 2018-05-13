
//SPOJ FASTFLOW, 100ms
// isap, n^3, point starts at 0

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 2500 + 100;
const int MAXM = 40000;
const int INF = 0x3f3f3f3f;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

struct Edge {
    int to, next, cap, flow;
    void c(int t, int n, int c, int f) {
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

void addedge(int u, int v, int w, int rw = 0) {
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

long long isap(int start, int end, int N) {
    BFS(start, end);
    memcpy(cur, head, sizeof(head));
    int top = 0, u = start;
    long long ans = 0;
    while (dep[start] < N) {
        if (u == end) {
            int Min = INF, inser;
            for (int i = 0; i < top; i++)
                if(Min > edge[S[i]].cap - edge[S[i]].flow) {
                    Min = edge[S[i]].cap - edge[S[i]].flow;
                    inser = i;
                }
            for (int i = 0; i < top; i++) {
                edge[S[i]].flow += Min;
                edge[S[i] ^ 1].flow -= Min;
            }
            ans += Min;
            top = inser;
            u = edge[S[top] ^ 1].to;
            continue;
        }
        bool flag = false;
        int v;
        for (int i = cur[u]; i != -1; i = edge[i].next) {
            v = edge[i].to;
            if (edge[i].cap - edge[i].flow && dep[v] + 1 == dep[u]) {
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
            if(edge[i].cap - edge[i].flow && dep[edge[i].to] < Min) {
                Min = dep[edge[i].to];
                cur[u] = i;
            }
        gap[dep[u]]--;
        if (!gap[dep[u]])
            return ans;
        dep[u] = Min + 1;
        gap[dep[u]]++;
        if(u != start)
            u = edge[S[--top] ^ 1].to;
    }
    return ans;
}

int n, m;
inline bool isvalid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int main() {
    long long costa, costb;
    while(scanf("%d%d%lld%lld", &n, &m, &costa, &costb) == 4) {
        init();
        int SS = n * m + 1;
        int TT = n * m + 2;
        char s[100][100];
        for (int i = 0; i < n; i++) {
            scanf("%s", s[i]);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                /* pr(i) pr(j) pr(i * m + j + 1) pn */
                if (s[i][j] == '#') addedge(i * m + j + 1, TT, costb);
                else addedge(SS, i * m + j + 1, costb);
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (isvalid(x, y)) addedge(i * m + j + 1, x * m + y + 1, costa);
                }
            }
        }
        long long ans = isap(SS, TT, TT);
        printf("%lld\n", ans);
    }
    return 0;
}
