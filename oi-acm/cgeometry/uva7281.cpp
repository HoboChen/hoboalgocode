#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # " << endl;
#define pn cout << endl;

inline void px(string & s) { cout << s << endl; }

const int maxn = 10000;
const int inf = 0x3e3e3e3e;
const long long llinf = (long long)0x3e3e3e3e * 0x3e3e3e3e;

const double pi = acos(-1.0);

inline double sqr (double x) { return x * x; }

const double eps = 1e-8;
int cmp(double x) {
    if (fabs(x) < eps) return 0;
    if (x > 0) return 1;
    return -1;
}

struct point {
    double x, y;
    point() { }
    point(double x, double y) : x(x), y(y) {  }
    void input() { scanf("%lf%lf", &x, &y); }
    friend point operator + (const point & a, const point & b) { return point(a.x + b.x, a.y + b.y); }
    friend point operator - (const point & a, const point & b) { return point(a.x - b.x, a.y - b.y); }
    friend point operator * (const point & a, const double & b) { return point(a.x * b, a.y * b); }
    friend point operator / (const point & a, const double & b) { return point(a.x / b, a.y / b); }
    friend bool operator == (const point & a, const point & b)  { return cmp(a.x - b.x) == 0 && cmp(a.y - b.y) == 0; }
    double norm() {
        return hypot(x, y);
    }
};

double det(const point & a, const point & b) {
    return a.x * b.y - a.y * b.x;
}
double dot(const point & a, const point & b) {
    return a.x * b.x + a.y * b.y;
}

double dist(const point & a, const point & b) {
    return (a - b).norm();
}
point rotate_point(const point & p, double A) {
    double tx = p.x, ty = p.y;
    return point(tx * cos(A) - ty * sin(A), tx * sin(A) + ty * cos(A));
}

struct polygon_convex {
    vector<point> P;
    polygon_convex(int Size = 0) { P.resize(Size); }
};

bool comp_less(const point & a, const point & b) {
    return cmp(a.x - b.x) < 0 || cmp(a.x - b.x) == 0 && cmp(a.y - b.y) < 0;
}

polygon_convex convexHull(vector<point> a) {
    polygon_convex res(2 * a.size() + 5);
    sort(a.begin(), a.end(), comp_less);
    a.erase(unique(a.begin(), a.end()), a.end());
    int m = 0;
    for (int i = 0; i < a.size(); ++i) {
        while (m > 1 && cmp(det(res.P[m-1] - res.P[m - 2], a[i] - res.P[m - 2])) <= 0)
            --m;
        res.P[m++] = a[i];
    }
    int k = m;
    for (int i = int(a.size()) - 2; i >= 0; --i) {
        while (m > k && cmp(det(res.P[m - 1] - res.P[m - 2], a[i] - res.P[m - 2])) <= 0)
            --m;
        res.P[m++] = a[i];
    }
    res.P.resize(m);
    if (a.size() > 1) res.P.resize(m - 1);
    return res;   
}
    
int containOlogn(const polygon_convex & a, const point & b) {
    int n = a.P.size();
    if (n <= 2) return 0;
    point g = (a.P[0] + a.P[n / 3] + a.P[2 * n / 3]) / 3.0;
    int l = 0, r = n;
    while ( l + 1 < r) {
        int mid = (l + r) / 2;
        if (cmp(det(a.P[l] - g, a.P[mid] - g)) > 0) {
            if (cmp(det(a.P[l] - g, b - g)) >= 0 && cmp(det(a.P[mid] - g, b - g)) < 0)
                r = mid;
            else 
                l = mid;
        }
        else {
            if (cmp(det(a.P[l] - g, b- g)) < 0 && cmp(det(a.P[mid] - g, b - g)) >= 0)
                l = mid;
            else 
                r = mid;
        }
    }
    r %= n;
    int z = cmp(det(a.P[r] - b, a.P[l] - b)) - 1;
    if ( z == -2) return 1;
    return z;
}
int main() {
    // freopen("in", "r", stdin);
    int L;
    while (scanf("%d", &L) == 1 && L) {
        polygon_convex hobo(L);
        for (int i = 0; i < L; i++) { 
            hobo.P[i].input();
            // pr(hobo.P[i].x)
            // pr(hobo.P[i].y);
            // pn
        }
        polygon_convex eddie;
        eddie = convexHull(hobo.P);
        int S;
        scanf("%d", &S);
        // pr(S)
        long long ans = 0;
        /*
        for (int i = 0; i < eddie.P.size(); i++) {
            pr(eddie.P[i].x)
            pr(eddie.P[i].y)
            pn
        } 
        */
        for (int i = 0; i < S; i++) {
            point t;
            t.input();
            if (containOlogn(eddie, t)) {
                // pr(t.x) pr(t.y) pn
                ans ++;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
