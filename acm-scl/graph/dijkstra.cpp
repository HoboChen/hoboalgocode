#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 1000;
const int maxm = 100000;
const int INF = 0x3e3e3e3e;

struct edge { int to, next, dist; };
edge e[maxm];
int head[maxn], tot, d[maxn];

int n, m;

void addedge(int u, int v, int w) {
	e[++tot].to = v;
	e[tot].dist = w;
	e[tot].next = head[u];
	head[u] = tot;
}

struct cmp {
	bool operator() (const pair<int, int> & x, const pair<int, int> & y) const {
		return y.second < x.second;
	}
};


void dijktra(int S, int * d, edge * e) {
	int vis[maxn];
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++)
		d[i] = INF;
	d[S] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> Q;
	Q.push(make_pair(S, d[S]));
	while (!Q.empty()) {
		pair<int, int> no = Q.top(); Q.pop();
		int u = no.first;
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = head[u]; ~i; i = e[i].next) {
			edge ed = e[i];
			if (d[ed.to] > d[u] + ed.dist) {
				d[ed.to] = d[u] + ed.dist;
				Q.push(make_pair(ed.to, d[ed.to]));
			}
		}
	}
}

int main() {
	tot = 0;
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int t1, t2, t3;
		scanf("%d%d%d", &t1, &t2, &t3);
		addedge(t1, t2, t3);
		// addedge(t2, t1);
	}

	return 0;
}

