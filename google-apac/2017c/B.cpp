#include <bits/stdc++.h>

using namespace std;

const int maxn = 3000 + 1000;

#define pr(x) cout << #x << " = " << x << endl;
#define pn cout << endl;

int M[maxn][maxn], S[maxn][maxn];

template <typename _t>
_t min(_t x, _t y, _t z) {
	return min(min(x, y), min(x, z));
}

int main() {
	int t, kase = 0;
	scanf("%d", &t);
	while (t--) {
		memset(M, 0, sizeof(M));
		memset(S, 0, sizeof(S));
		int R, C, K;
		scanf("%d %d %d\n", &R, &C, &K);
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				M[i][j] = 1;
		for (int i = 0; i < K; i++) {
			int x, y;
			scanf("%d %d\n", &x, &y);
			M[x][y] = 0;
		}
		for (int i = 0; i < R; i++)
			S[i][0] = M[i][0];
		for (int j = 0; j < C; j++)
			S[0][j] = M[0][j];
		for (int i = 1; i < R; i++) {
			for (int j = 1; j < C; j++) {
				if (M[i][j]) 
					S[i][j] = min(S[i - 1][j - 1], S[i - 1][j], S[i][j - 1]) + 1;
				else 
					S[i][j] = 0;
			}
		}
		long long ret = 0;
		for (int i = 0; i < R; i++) 
			for (int j = 0; j < C; j++)
				ret += S[i][j];
        printf("Case #%d: %lld\n", ++kase, ret);
	}
    return 0;
}
