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

const int maxn = 300;
const double eps = 1e-10;

int st[maxn][maxn][9], n, a[maxn], mt[maxn][maxn][9];
int ma[maxn][maxn], ms[maxn][maxn], mm[maxn][maxn];

void getST(int r) {
    int m = log(n) / log(2);
    for (int i = 1; i <= n; i++) {
        mt[r][i][0] = mm[r][i];
    	st[r][i][0] = ms[r][i];
    }
    for (int j = 1; j <= m; j++)
        for (int i = n; i > 0; i--) {
            st[r][i][j] = st[r][i][j - 1];
            mt[r][i][j] = mt[r][i][j - 1];
            if (i + (1 << (j - 1)) <= n) {
                st[r][i][j] = max(st[r][i][j], st[r][i + (1 << (j - 1))][j - 1]);
                mt[r][i][j] = min(mt[r][i][j], mt[r][i + (1 << (j - 1))][j - 1]);
            }
    }
}

pair<int, int> query(int l, int r, int row) {
    int k = log(r - l + 1) / log(2);
    return make_pair(
    	max(st[row][l][k], st[row][r - (1 << k) + 1][k]),
    	min(mt[row][l][k], mt[row][r - (1 << k) + 1][k])
    	);
}



int main() {
	int N, B, K;
	scanf("%d%d%d", &N, &B, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++){
			scanf("%d", &ma[i][j]);
		}
	}
	n = N;
	memcpy(ms, ma, sizeof(ma));
	memcpy(mm, ma, sizeof(ma));
	for (int i = 1; i <= N - B + 1; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 1; k < B; k++) {
				mm[i][j] = min(mm[i][j], mm[i + k][j]);
				ms[i][j] = max(ms[i][j], ms[i + k][j]);
			}
		}
		getST(i);
	}
	for (int i = 0; i < K; i++) {
		int r, b;
		scanf("%d%d", &r, &b);
		pair<int, int> ans = query(b, b + B - 1, r);
		printf("%d\n", ans.first - ans.second);
	}
    return 0;
}

