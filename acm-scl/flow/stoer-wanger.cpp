// poj2914, 3219ms, 1864kb
// stoer_wanger, n^3, point starts at 0
// http://www.cnblogs.com/wally/p/3281983.html

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 555;
const int inf = 0x3f3f3f3f;

int v[MAXN], dist[MAXN], map[MAXN][MAXN], n, m;
bool vis[MAXN];

int stoerwanger(int n) {
    int res = inf;
    for(int i = 0; i < n; i++) v[i] = i;
    while (n > 1) {
        int k = 0, pre = 0;
        memset(vis, false, sizeof(vis));
        memset(dist, 0, sizeof(dist));
        for(int i = 1; i < n; i++) {
            k = -1;
            for(int j = 1; j < n; j++){
                if(!vis[v[j]]) {
                    dist[v[j]] += map[v[pre]][v[j]];
                    if(k == -1 || dist[v[k]] < dist[v[j]]) {
                        k = j;
                    }
                }
            }
            vis[v[k]] = true;
            if(i == n - 1) {
                res = min(res, dist[v[k]]);
                for(int j = 0; j < n; j++) {
                    map[v[pre]][v[j]] += map[v[j]][v[k]];
                    map[v[j]][v[pre]] += map[v[j]][v[k]];
                }
                v[k] = v[--n];
            }
            pre = k;
        }
    }
    return res;
}

int main() {
    int u, v, w;
    while(~scanf("%d%d", &n, &m)) {
        memset(map, 0, sizeof(map));
        while (m--) {
            scanf("%d%d%d", &u, &v, &w);
            map[u][v] += w;
            map[v][u] += w;
        }
        int ans = stoerwanger(n);
        printf("%d\n",ans);
    }
    return 0;
}

