#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxn = 7000;

vector<int> G[maxn];
int dp[maxn][2];
int value[maxn];
int vis[maxn];

void dfs(int node) {
    if (vis[node]) {
        return;
    }
    vis[node] = 1;
    dp[node][1] = value[node];
    for (int i = 0; i < G[node].size(); i++) {
        if (!vis[G[node][i]]) {
            dfs(G[node][i]);
            dp[node][0] += max(dp[G[node][i]][0], dp[G[node][i]][1]);
            dp[node][1] += dp[G[node][i]][0];
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &value[i]);
    }
    int k, l;
    while (scanf("%d %d", &k, &l)) {
        if (k == 0 && l == 0) {
            break;
        }
        G[k].push_back(l);
        G[l].push_back(k);
    }
    dfs(1);
    printf("%d", max(dp[1][0], dp[1][1]));
    return 0;
}