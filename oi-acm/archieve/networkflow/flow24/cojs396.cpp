#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>

using namespace std;

#define pr(x) cout << #x << " = " << x << " $";
#define pn cout << endl;

const int MAXN = 20000 + 10000;
const int MAXM = 70000 + 10000;
const int INF = 0x3f3f3f3f;

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

const int maxn = 1600;
vector<int> sq[maxn];
set<int> sqq;

void work() {
    for (int i = 1; i <= maxn; i++)
        sqq.insert(i * i);
    for (int i = 1; i <= maxn; i++) {
        for (int j = i + 1; j <= maxn; j++) {
            if (sqq.count(i + j))
                sq[i].push_back(j);
        }
    }
}

int n, m;

bool check(int mid) {
    init();
    for (int i = 1; i <= mid; i++) {
        for (int j = 0; j < sq[i].size(); j++) {
            if (sq[i][j] > mid) break;
            addedge(i * 2, sq[i][j] * 2 + 1, 1);
        }
    }
    int SS = mid * 2 + 2, TT = mid * 2 + 3;
    for (int i = 1; i <= mid; i++) {
        addedge(SS, i * 2, 1);
        addedge(i * 2 + 1, TT, 1);
    }
    long long ret = isap(SS, TT, TT);
    return (mid - ret) <= n;
}

int main() {
    work();
    scanf("%d", &n);
    int l = 0, r = 1602, mid, ans;
    while (r > l) {
        mid = l + (r - l) / 2;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        }
        else 
            r = mid;
    }
    cout << ans << endl;
    return 0;
}
