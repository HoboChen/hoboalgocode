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

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 5000;
const double eps = 1e-10;

int f[maxn];
double s[maxn];
       
struct line {
    double l, r, y;
    int s;
    line() { } 
    line(double l, double r, double y, int s) : l(l), r(r), y(y), s(s) { }
    bool operator < (const line & s) const {
        return y < s.y;
    }
};
 
double x[maxn];
line l[maxn];

void pushup(int u, int l, int r) {
    if (f[u])
        s[u] = x[r + 1] - x[l];
    else if (l == r) 
        s[u] = 0;
    else s[u] = s[u * 2] + s[u * 2 + 1];
}

void update(int u, int l, int r, int ql, int qr, int d) {
    if (ql <= l && qr >= r) {
        f[u] += d;
        pushup(u, l, r);
        return ;
    }
    int m = (l + r) / 2;
    if (qr <= m) update(u * 2, l, m, ql, qr, d);
    else if (ql > m) update(u * 2 + 1, m + 1, r, ql, qr, d);
    else {
        update(u * 2, l, m, ql, qr, d);
        update(u * 2 + 1, m + 1, r, ql, qr, d);
    }
    pushup(u, l, r);
}

int main() {
    int n, c = 0;
    while (scanf("%d", &n) == 1 && n) {
        printf("Test case #%d\n", ++c);
        memset(f, 0, sizeof(f));
        memset(s, 0, sizeof(s));
        int nu = 0;
        for (int i = 0; i < n; i++) {
            double t1, t2, t3, t4;
            scanf("%lf%lf%lf%lf", &t1, &t2, &t3, &t4);
            l[++nu] = line(t1, t3, t2, 1);
            x[nu] = t1;
            l[++nu] = line(t1, t3, t4, -1);
            x[nu] = t3;
        }
        sort(x + 1, x + 1 + nu);
        sort(l + 1, l + 1 + nu);
        int k = 1;
        for (int i = 2; i <= nu; i++) {
            if (x[i] != x[i + 1]) 
                x[++k] = x[i];
        }
        double ans = 0;
        for (int i = 1; i < nu; i++) {
            int ll = lower_bound(x + 1, x + 1 + k, l[i].l) - x;
            int rr = lower_bound(x + 1, x + 1 + k, l[i].r) - x - 1;
            update(1, 1, k, ll, rr, l[i].s);
            ans += s[1] * (l[i + 1].y - l[i].y);
        }
        printf("Total explored area: %.2f\n\n", ans);
    }
    return 0;
}
