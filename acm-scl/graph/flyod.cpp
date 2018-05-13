
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

const int maxn = 1000;
const int inf = 0x3e3e3e3e;
const long long llinf = (long long)0x3e3e3e3e * 0x3e3e3e3e;

const double eps = 1e-10;

int g[maxn][maxn];
int dis[maxn][maxn];

void floyd(int g[][maxn], int dis[][maxn], int n) {
    // memcpy(dis, g, sizeof(g));
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
}

int main() {
    if (fio) freopen("in", "r", stdin);

    return 0;
}
