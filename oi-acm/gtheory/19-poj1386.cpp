
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

#ifdef ONLINE_JUDGE
    #define fio 0
#else
    #define fio 1
#endif

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

inline void px(string s) { cout << s << ends; }

const int maxn = 1000;
const double eps = 1e-10;

int p[maxn];

int find(int x, int *p) { return p[x] == x ? x : p[x] = find(p[x], p); }

void merge(int i, int j, int *p) {
    int x = find(i, p), y = find(j, p);
    p[y] = x;
}

void init(int * p, int n) {
	for (int i = 1; i <= n; i++)
		p[i] = i;
}

int din[maxn], dout[maxn];
int vis[maxn];

void addedge(int u, int v, int *p) {
    merge(u, v, p);
    vis[u] = 1;
    vis[v] = 1;
    din[u] += 1;
    dout[v] += 1;
}

bool hasUnrectedEulerPath(int *p, int *din, int *dout, int n) {
    int s = 0;
    int t = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) continue;
        if (p[i] != p[1]) return 0;
        if (din[i] == dout[i]) continue;
        else if (din[i] == dout[i] + 1)
            s++;
        else if (din[i] + 1 == dout[i])
            t++;
        else return 0;
    }
    if (s == 1 && t == 1)
        return 1;
    return 0;
}

bool hasUndiretedEulerCircle(int *p, int *din, int *dout, int n) {
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) continue;
        if (find(i, p) != find(1, p)) return 0;
        if (din[i] != dout[i]) return 0;
    }
    return 1;
}

void init() {
    init(p, 26);
    memset(din, 0, sizeof(din));
    memset(dout, 0, sizeof(dout));
    memset(vis, 0, sizeof(vis));
}

int main() {
    if (fio) freopen("in", "r", stdin);
    int t, c = 0;      
    cin >> t;
    for (int i = 1; i <= t; i++) {
        init();
        int n; 
        cin >> n;
        string s;
        for (int j = 1; j <= n; j++) {
            cin >> s;
            int len = s.size();
            addedge(s[0] - 'a' + 1, s[len - 1] - 'a' + 1, p);
        }
        bool f1 = hasUnrectedEulerPath(p, din, dout, 26);
        bool f2 = hasUndiretedEulerCircle(p, din, dout, 26);
        if (f1 || f2 || n == 1)
            printf("Ordering is possible.\n");
        else 
            printf("The door cannot be opened.\n");
    }
    return 0;
}
