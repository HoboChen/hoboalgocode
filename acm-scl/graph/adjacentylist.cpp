
#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 1000;
const int maxm = 100000;
const double eps = 1e-10;

struct edge { int to, next; };
edge e[maxm];
int head[maxn];
int tot;

void addedge(int u, int v) {
    e[++tot].to = v;
    e[tot].next = head[u];
    head[u] = tot;
}

int main() {
    int n, m;
    tot = 0;
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int t1, t2;
        scanf("%d%d", &t1, &t2);
        addedge(t1, t2);
        // addedge(t2, t1);
    }

    return 0;
}
