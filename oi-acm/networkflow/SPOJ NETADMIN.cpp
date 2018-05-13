
//SPOJ FASTFLOW, 100ms
// isap, n^3, point starts at 0

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

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

const int maxn = 500 + 10;
const int maxm = maxn * maxn;
const int inf = 0x3e3e3e3e;

int user[maxn], uu[maxm], vv[maxm];
int SS, n, m, k;
bool check(int cc) {
    init();
    for (int i = 1; i <= k; i++) {    
        addedge(SS, user[i], 1);
    }
    for (int i = 1; i <= m; i++) {
        addedge(uu[i], vv[i], cc, cc);
    }
    long long ret = isap(SS, 1, n + 1);
    return ret >= k;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &m, &k);
        SS = n + 1;
        for (int i = 1; i <= k; i++) 
            scanf("%d", &user[i]);
        for (int i = 1; i <= m; i++) 
            scanf("%d%d", &uu[i], &vv[i]);
        int l = 0, r = inf, mid, ans;
        while (l < r) {
            mid = (l + r) / 2;
            if (check(mid)) {
                ans = mid;
                r = mid;
            }
            else 
                l = mid + 1;
        }
        cout << ans << endl;
    }
    return 0;
}
