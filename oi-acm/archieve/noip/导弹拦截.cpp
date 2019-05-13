// Dilworth定理，不上升子序列的最小划分数等于最长上升子序列的长度。

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000 + 100;

int get_max(int* f, int n) {
    int ret = -1;
    for (int i = 1; i <= n; i++) {
        ret = max(ret, f[i]);
    }
    return ret;
}

int main() {
    int n;
    int h[maxn], f[maxn], g[maxn];
    cin >> n;
    for (int i = 1; i <= n; i++) {
        f[i] = g[i] = 1;
    }
	for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (h[i] <= h[j]) {
                f[i] = max(f[i], f[j] + 1);
            }
            else {
                g[i] = max(g[i], g[j] + 1);
            }
        }
    }
    cout << get_max(f, n) << ' ';
    cout << get_max(g, n) << endl;
	return 0;
}