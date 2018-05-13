
const int maxn = 10000;

int L[maxn];

bool toposort(int n, vector<int> & g) {
    int * du = new int[maxn];
    memset(du, 0, sizeof(int) * maxn);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < g[i].size(); j++)
            du[g[i][j]]++;
    int tot = 0;
    queue<int> Q;
    for (int i = 0; i < n; i++)
        if (!du[i]) Q.push(i);
    while (!Q.empty()) {
        int x = Q.front(); Q.pop();
        L[tot++] = x;
        for (int j = 0; j < g[x].size(); j++) {
            int t = g[x][j];
            du[t]--;
            if (!du[t]) Q.push(t);
        }
    }
    delete du;
    return tot == n;
}
