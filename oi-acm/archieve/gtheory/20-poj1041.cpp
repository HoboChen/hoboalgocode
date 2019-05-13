
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>

#ifdef ONLINE_JUDGE
    #define fio 0
#else
    #define fio 1
#endif

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;
inline void px(string s) { cout << s << ends; }

const int maxn = 100;
const int maxm = 2000;
const double eps = 1e-10;


int ma[maxn][maxm];
bool todo, vis[maxm];
int deg[maxn], start, cnt, maxstreet;
/* map<int, int> e; */
stack<int> ans;


void init() {
    todo = 0;
    cnt = 0;
    /* e.clear(); */
    while (!ans.empty())
        ans.pop();
    memset(deg, 0, sizeof(deg));
    memset(vis, 0, sizeof(vis));
    memset(ma, 0, sizeof(ma));
}


void addedge(int x, int y, int z) {
    /* int t1 = x * maxm + z; */
    /* int t2 = y * maxm + z; */
    /* e[t1] = y; */
    /* e[t2] = x; */
    ma[x][z] = y;
    ma[y][z] = x;
    cnt++;
    maxstreet = max(maxstreet, z);
    if (cnt == 1) start = min(x, y);
    deg[x] += 1;
    deg[y] += 1;
    todo = 1;
}

void dfs(int s) {
    for (int i = 1; i <= maxstreet; i++) {
        /* int t = s * maxm + i; */
        int t = ma[s][i];
        if (t && !vis[i]) {
            vis[i] = 1;
            dfs(t);
            ans.push(i);
        }
    }
}

bool solve() {
    int degsum = 0;
    for (int i = 1; i <= maxn - 1; i++) 
        degsum += deg[i];
    if (!degsum) return 0;
    for (int i = 1; i <= maxn - 1; i++)
        if (deg[i] % 2 != 0) {
            printf("Round trip does not exist.\n");
            init();
            return 1;
        }
    dfs(start);
    while (!ans.empty()) {
        int x = ans.top();
        ans.pop();
        printf("%d ", x);
    }
    printf("\n");
    init();
    return 1;
}

int read() {
    int x, y, z;
    while (scanf("%d %d", &x, &y) == 2) {
        if (x == 0 && y == 0) {
            return solve();
        }
        int z;
        scanf("%d", &z);
        addedge(x, y, z);
    }
    return 1;
}

int main() {
    if (fio) freopen("in", "r", stdin);
    while (read()) {

    }
    return 0;
}
