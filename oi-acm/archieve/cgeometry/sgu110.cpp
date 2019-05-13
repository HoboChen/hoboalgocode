#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

inline double sqr(double x) { return x * x; }

const int maxn = 50 + 10;
const double inf = (1LL<<60);
const double eps = 1e-10;

struct Point3 {
    double x, y, z;
    Point3() {}
    Point3(double x, double y, double z): x(x), y(y), z(z) {}
    
    double abs2() {return x * x + y * y + z * z; }
    double dot(const Point3 & b) { return x * b.x + y * b.y + z * b.z; }

    Point3 operator + (const Point3 & b) { return Point3(x + b.x, y + b.y, z + b.z); }
    Point3 operator - (const Point3 & b) { return Point3(x - b.x, y - b.y, z - b.z); }
    Point3 operator * (const double & b) { return Point3(x * b, y * b, z * b); }
    Point3 operator / (const double & b) { return Point3(x / b, y / b, z / b); }

    void read() {
        scanf("%lf%lf%lf", &x, &y, &z);
    }
};

Point3 c[maxn];
double r[maxn], tt;
  
inline int next(int n, Point3 dir, Point3 start) {
    int w = 0;
    double a, b, cc, delta, tm;
    tt = inf;
    for (int i = 1; i <= n; i++) {
        a = dir.abs2();
        b = (start - c[i]).dot(dir) * 2.0;
        cc = (start - c[i]).abs2() - sqr(r[i]);
        if ((delta = sqr(b) - 4 * a * cc) > -eps) {
            if (fabs(delta) < eps)
                delta = 0;
            else
                delta = sqrt(delta);
            tm = (-b + delta) / a / 2;
            if (tm > eps && tm < tt) {
                tt = tm;
                w = i;
            }
            tm = (-b - delta) / a / 2;
            if (tm > eps && tm < tt) {
                tt = tm;
                w = i;
            }
        }
    }
    return w;  
}

int main() {
    int n;
    scanf("%d", &n);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        c[i].read();
        scanf("%lf", &r[i]);
    }
    Point3 start, end, dx;
    start.read();
    end.read();
    dx = end - start;
    while (1) {
        int t = next(n, dx, start);
        if (t == 0) break;
        printf("%d ",t);
        cnt++;
        start = start + dx * tt;
        Point3 R = start - c[t];
        dx = dx - R / R.abs2() * 2 * R.dot(dx);
        if (cnt == 10) break;
    }
    if (cnt == 10 && next(n, dx, start)) printf("etc.");
    printf("\n");
    return 0;
}
