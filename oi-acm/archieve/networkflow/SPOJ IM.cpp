

// isap, n^3, point starts at 0

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 70000 + 10000;
const int MAXM = 400000 + 10000;
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

int main() {
	int t;
    scanf("%d", &t);
    while (t--) {
        init();
        int n, m;
        scanf("%d%d", &n, &m);
        int SS = 2 * n + 1;
        int TT = 2 * n + 2;
        addedge(SS, n + 2, 2);
        addedge(1 + n, TT, 1);
        addedge(3 + n, TT, 1);
        addedge(3, 3 + n, 1);
        addedge(1, 1 + n, 1);
        for (int i = 4; i <= n; i++) 
            addedge(i, i + n, 1);
        for (int i = 1; i <= m; i++) {
            int t1, t2;
            scanf("%d%d", &t1, &t2);
       if (t1 < 1 || t1 > n || t2 < 1 || t2 > n) continue;
            addedge(t1 + n, t2, 1);
            addedge(t2 + n, t1, 1);
        }
        long long ret = isap(SS, TT, 2 * n + 2);
        if (ret == 2)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
