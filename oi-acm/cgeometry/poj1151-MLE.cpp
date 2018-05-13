#include <bits/stdc++.h>

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
    line(double l, double r, double y, int s) : l(l), r(r), y(y), s(s) { }
    bool operator < (const line & s) const {
        return y < s.y;
    }
};

vector<double> x;
vector<line> l;
 
void pushup(int u, int l, int r) {
    if (f[u])
        s[u] = x[r] - x[l - 1];
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
        x.clear();
        l.clear();
        for (int i = 0; i < n; i++) {
            double t1, t2, t3, t4;
            scanf("%lf%lf%lf%lf", &t1, &t2, &t3, &t4);
            l.push_back(line(t1, t3, t2, 1));
            x.push_back(t1);
            l.push_back(line(t1, t3, t4, -1));
            x.push_back(t3);;
        }
        sort(x.begin(), x.end());
        sort(l.begin(), l.end());
        int nodesize = unique(x.begin(), x.end()) - x.begin();
        int p = l.size();
        double ans = 0;
        for (int i = 0; i < p - 1; i++) {
            int ll = lower_bound(x.begin(), x.end(), l[i].l) - x.begin() + 1;
            int rr = lower_bound(x.begin(), x.end(), l[i].r) - x.begin();
            update(1, 1, nodesize, ll, rr, l[i].s);
            ans += s[1] * (l[i + 1].y - l[i].y);
        }
        printf("Total explored area: %.2f\n\n", ans);
    }
    return 0;
}
