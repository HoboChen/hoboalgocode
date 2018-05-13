#include <bits/stdc++.h>

using namespace std;

const int maxn = 10000;

#define pr(x) cout << #x << " = " << x << " % ";
#define pn cout << endl;

bool vis[maxn];

inline bool HasCommon(const vector<int> & x, const vector<int> & y) {
	unordered_set<int> q(x.begin(), x.end());
	for (int i = 0; i < y.size(); i++) {
		if (q.count(y[i]) && vis[y[i]])
			return 1;
	}
	return 0;
}

int main() {
	int t, kase = 0;
	scanf("%d", &t);
	while (t--) {
		bool ans;
		vector<pair<int, int> > s;
		memset(vis, 1, sizeof(vis));
		int n;
		scanf("%d\n", &n);
		for (int i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d\n", &x, &y);
			s.push_back(make_pair(x, y));
		}
		while (1) {
			int xmax = 0, ymax = 0;
			for (int i = 0; i < s.size(); i++) {
				if (vis[i]) xmax = max(xmax, s[i].first);
				if (vis[i]) ymax = max(ymax, s[i].second);
			}
			if (xmax == 0) { ans = 0; break; }
			vector<int> xm, ym;
			for (int i = 0; i < s.size(); i++) {
				if (s[i].first == xmax) xm.push_back(i);
				if (s[i].second == ymax) ym.push_back(i);
			}
			if (HasCommon(xm, ym)) { ans = 1; break; }
			for (int i = 0; i < xm.size(); i++) vis[xm[i]] = 0;
			for (int i = 0; i < ym.size(); i++) vis[ym[i]] = 0;
		}
        printf("Case #%d: ", ++kase);
        if (ans) printf("YES\n");
        else printf("NO\n");
	}
    return 0;
}