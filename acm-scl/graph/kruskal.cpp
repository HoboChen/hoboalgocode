#include <bits/stdc++.h>

#define pr(x) cout << #x << " = " << x << " $";

using namespace std;

#define scan(x) scanf("%d", &x)
#define scan2(x, y) scanf("%d%d", &x, &y)

const int maxn = 10000 + 5000;
int m, n, w[maxn], p[maxn], r[maxn], u[maxn], v[maxn];
int ans, cnt;

int find(int x) {
	return p[x] == x ? x : p[x] = find(p[x]);
}

bool cmp(int i, int j) {
	return w[i] < w[j];
}

void merge(int i, int j) {
	int x = find(i);
	int y = find(j);
	if (x > y) p[y] = x;
	else p[x] = y;
}

void MST() {
	sort(r, r + cnt, cmp);
	for (int i = 0; i < cnt; i++) {
		int e = r[i];
		int x = find(u[e]);
		int y = find(v[e]);
		if (x != y) {
			ans += w[e];
			p[x] = y;
		}
	}
}

void init() {
	for (int i = 0; i < n; i++) p[i] = i;
	for (int i = 0; i < cnt; i++) r[i] = i;
}

int main() {
	while (scan(n) != EOF) {
		ans = 0, cnt = 0;
		int x, y;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scan(x);
				if (j > i) {
					w[cnt] = x;
					u[cnt] = i;
					v[cnt] = j;
					cnt++;
				}
			}
		}
		init();
		int qt;
		scan(qt);
		for (int i = 0; i < qt; i++) {
			scan2(x, y);
			if (x > y) swap(x, y);
			merge(x - 1, y - 1);
		}
		MST();
		cout << ans << endl;
	}
	return 0;
}
