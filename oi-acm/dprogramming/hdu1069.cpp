
#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 1000;
const double eps = 1e-10;
const int inf = 0x3e3e3e;

struct triple {
    int x, y, z;
    triple(int x, int y, int z) : x(x), y(y), z(z) { }
};

vector<triple> q;

int f[maxn];

int DAG_DP(int u, vector<triple> & q) {
    if (f[u] >= 0) return f[u];
    f[u] = 0;
    for (int v = 0; v < q.size(); v++)
        if ((q[v].x < q[u].x && q[v].y < q[u].y) || (q[v].y < q[u].x && q[v].x < q[u].y))
            f[u] = max(f[u], DAG_DP(v, q) + q[v].z);
    return f[u];
}

int main() {
    int n, c = 0;
    while (scanf("%d", &n) == 1 && n) {
        q.clear();
        memset(f, -1, sizeof(f));
        for (int i = 0; i < n; i++) {
            int t1, t2, t3;
            scanf("%d%d%d", &t1, &t2, &t3);
            q.push_back(triple(t1, t2, t3));
            q.push_back(triple(t1, t3, t2));
            q.push_back(triple(t2, t3, t1));
        }
        q.push_back(triple(inf, inf, inf));
        int s = q.size() - 1;
        printf("Case %d: maximum height = %d\n", ++c, DAG_DP(s, q));
    }
    return 0;
}
