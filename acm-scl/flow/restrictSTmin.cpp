
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
    #define fio 0
#else
    #define fio 1
#endif

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;
inline void px(string s) { cout << s << ends; }

const int inf = 0x3e3e3e3e;
const long long llinf = (long long)0x3e3e3e3e * 0x3e3e3e3e;

const double eps = 1e-10;

const int maxp = 300;
const int maxe = 20000;

struct Edge {
    int t, n, c, f; // to, next, cap, flow
    void cc(int tb, int nb, int cb, int fb) {
        t = tb;
        n = nb;
        c = cb;
        f = fb;
    }
}es[maxe];

int tol, head[maxp], gap[maxp], dep[maxp], cur[maxp];

void init() {
    tol = 0;
    memset(head, -1, sizeof(head));
}

void addedge(int u, int v, int w, int rw = 0) {
    es[tol].cc(v, head[u], w, 0);
    head[u] = tol++;
    es[tol].cc(u, head[v], rw, 0);
    head[v] = tol++;
}

int Q[maxp];

void BFS(int start, int end) {
    memset(dep, -1, sizeof(dep));
    memset(gap, 0, sizeof(gap));
    gap[0] = 1;
    int front = 0, rear = 0;
    dep[end] = 0;
    Q[rear++] = end;
    while(front != rear) {
        int u = Q[front++];
        for(int i = head[u]; i != -1; i = es[i].n) {
            int v = es[i].t;
            if (dep[v] != -1) continue;
            Q[rear++] = v;
            dep[v] = dep[u] + 1;
            gap[dep[v]]++;
        }
    }
}

int S[maxp];

long long isap(int start, int end, int N = maxp) {
    BFS(start, end);
    memcpy(cur, head, sizeof(head));
    int top = 0, u = start;
    long long ans = 0;
    while (dep[start] < N) {
        if (u == end) {
            int mm = inf, inser;
            for (int i = 0; i < top; i++)
                if(mm > es[S[i]].c - es[S[i]].f) {
                    mm = es[S[i]].c - es[S[i]].f;
                    inser = i;
                }
            for (int i = 0; i < top; i++) {
                es[S[i]].f += mm;
                es[S[i] ^ 1].f -= mm;
            }
            ans += mm;
            top = inser;
            u = es[S[top] ^ 1].t;
            continue;
        }
        bool f = false;
        int v;
        for (int i = cur[u]; i != -1; i = es[i].n) {
            v = es[i].t;
            if (es[i].c - es[i].f && dep[v] + 1 == dep[u]) {
                f = true;
                cur[u] = i;
                break;
            }
        }
        if (f) {
            S[top++] = cur[u];
            u = v;
            continue;
        }
        int mm = N;
        for(int i = head[u]; i != -1; i = es[i].n)
            if(es[i].c - es[i].f && dep[es[i].t] < mm) {
                mm = dep[es[i].t];
                cur[u] = i;
            }
        gap[dep[u]]--;
        if (!gap[dep[u]])
            return ans;
        dep[u] = mm + 1;
        gap[dep[u]]++;
        if(u != start)
            u = es[S[--top] ^ 1].t;
    }
    return ans;
}

const int maxn = 200;
int iin[maxn], iout[maxn];

bool isvalid(int virS) {
    for (int j = head[virS]; ~j; j = head[virS].next)
        if (edge[]) 


}

int main() {
    if (fio) freopen("in", "r", stdin);
    init();
    memset(iin, 0, sizeof(iin));
    memset(iout, 0, sizeof(iout));
	int n, m;
    scanf("%d%d", &n, &m);
    int virS = n + 1, virT = n + 2, S = 1, T = n;
    for (int i = 1; i <= m; i++) {
        int u, v, w, op;
        scanf("%d%d%d%d", &u, &v, &w, &op);
        if (op == 1) addedge(u, v, w);        
        else {
            addedge(u, v, 0);
            iout[u] += w;
            iin[v] += w;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (iout[i]) addedge(i, virT, iout[i]);
        if (iin[i]) addedge(virS, i, iin[i]);
    }
    addedge(T, S, inf);
    isap(S, T, n + 2);
    return 0;
}
