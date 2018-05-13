#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <ctime>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

#define Vector Point

const double eps = 1e-10;
#ifndef M_PI
const double M_PI = 3.1415926535897932384626434;
#endif
inline int sign(double a) {
    return a < -eps ? -1 : a > eps;
}

struct Point {
    double x,y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    Point operator + (const Point &p) const {return Point(x+p.x,y+p.y);}
    Point operator - (const Point &p) const {return Point(x-p.x,y-p.y);}
    Point operator * (double d) const {return Point(x*d,y*d);}
    Point operator / (double d) const {return Point(x/d,y/d);}
    bool  operator < (const Point &p) const {
        int c = sign(x-p.x);
        if (c)
            return c == -1;
        return sign(y-p.y) == -1;
    }
    double dot(const Point &p) {return x*p.x + y*p.y;}
    double det(const Point &p) const {return x*p.y - y*p.x;}
    double alpha() const {return atan2(y,x);} //return [-pi,pi]
    double distTo(const Point &p) const {
        double dx=x-p.x, dy=y-p.y;
        return hypot(dx,dy);
    }
    double alphaTo(const Point &p) const {
        double dx=x-p.x, dy=y-p.y;
        return atan2(dy,dx);
    }
    // clockwise
    Point rotAlpla(const double &alpha, const Point &o = Point(0,0)) const {
        double nx = cos(alpha)*(x-o.x)+sin(alpha)*(y-o.y);
        double ny = -sin(alpha)*(x-o.x)+cos(alpha)*(y-o.y);
        return Point(nx,ny)+o;
    }
    // anti-clockwise
    Point rot90() const {return Point(-y, x);}
    Point unit() {return *this/abs();}

    double abs() {return hypot(x,y);}
    double abs2() {return x*x+y*y;}
    void testWrite () {cout<<"("<<x<<","<<y<<")"<<" ";}
    double getrad() { // return [0, 2pi)
        double res = atan2(y, x);
        if (res < 0) res += 2 * M_PI;
        if (fabs(res - 2 * M_PI) < 1e-10) return 0;
        return res;
    }

    void read() {scanf("%lf%lf",&x,&y);}
    void write() {printf("%lf %lf ", x, y);}
};
#define cross(p1,p2,p3) ((p2.x-p1.x) * (p3.y-p1.y) - (p3.x-p1.x) * (p2.y-p1.y)) // (p2-p1).det(p3-p1)
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))

// ensure that two lines are not in coincidence
Point lineLineIntersect(Point p1, Point p2, Point q1, Point q2) {
    double a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}
/* double minDiff(double a,double b) { //a,b in [0,2pi) */
/*     return min(fabs(a-b), 2*M_PI-fabs(a-b)); */
/* } */

bool onSegment(Point p, Point a1, Point a2) {
    return sign((a1 - p).det(a2 - p)) == 0 && sign((a1 - p).dot(a2 - p)) < 0;
}

struct line {
    Point p;
    Vector v;
    double ang;
    line() { }
    line(Point p, Vector v):p(p), v(v) { ang = atan2(v.y, v.x); }
    bool operator < (const line & x) const {
        return ang < x.ang;
    }
};

vector<Point> cutPolygon(const vector<Point> & q, Point A, Point B) {
    vector<Point> ret;
    int n = q.size();
    for (int i = 0; i < n; i++) {
        Point C = q[i];
        Point D = q[(i + 1) % n];
        if (crossOp(A, B, C) >= 0)
            ret.push_back(C);
        if (sign((B - A).det(C- D)) != 0) {
            Point ip = lineLineIntersect(A, B - A, C, D - C);
            if (onSegment(ip, C, D))
                ret.push_back(ip);
        }
    }
    return ret;
}

bool onLeft(line l, Point p) {
    return l.v.det(p - l.p) >= 0;
}

Point lineLineIntersect(line a, line b) {
    return lineLineIntersect(a.p, a.p + a.v, b.p, b.p + b.v);
}

vector<Point> HalfplaneIntersection(vector<line> L) {
    int n = L.size();
    sort(L.begin(), L.end());

    int first, last;
    vector<Point> p(n);
    vector<line> q(n);
    vector<Point> ans;

    q[first = last = 0] = L[0];
    for(int i = 1; i < n; i++) {
        while(first < last && !onLeft(L[i], p[last - 1]))
            last--;
        while(first < last && !onLeft(L[i], p[first]))
            first++;
        q[++last] = L[i];
        if (fabs(q[last].v.det(q[last - 1].v)) < eps) {
            last--;
            if (onLeft(q[last], L[i].p))
                q[last] = L[i];
        }
        if (first < last)
            p[last - 1] = lineLineIntersect(q[last - 1], q[last]);
    }
    while (first < last && !onLeft(q[first], p[last - 1]))
        last--;
    if (last - first <= 1)
        return ans;
    p[last] = lineLineIntersect(q[last], q[first]);

    for (int i = first; i <= last; i++)
        ans.push_back(p[i]);
    return ans;
}

int V[110], U[110], W[110];

//多边形周长
double Circum(const vector<Point> &ps) {
    int n = ps.size();
    double ret = 0;
    for (int i=0;i<n;i++)
        ret += ps[i].distTo(ps[(i+1)%n]);
    return ret;
}

//有向面积
double calcArea(const vector<Point> &ps)  {
    int n = ps.size();
    double ret = 0;
    for (int i=0; i < n; i++)
        ret += ps[i].det(ps[(i+1) % n]);
    return ret / 2.0;
}

void test() {
    const double LARGE = 1e10;
    /* Point A(0, 0), B(LARGE, 0), C(LARGE, LARGE), D(0, LARGE); */
    Point A(-LARGE, -LARGE), B(LARGE, -LARGE), C(LARGE, LARGE), D(-LARGE, LARGE);
    vector<line> tmp;
    tmp.push_back(line(A, B-A));
    tmp.push_back(line(B, C-B));
    tmp.push_back(line(C, D-C));
    tmp.push_back(line(D, A-D));
    vector<Point> ans = HalfplaneIntersection(tmp);
    printf("%lf\n", calcArea(ans));
}

void addlarge(vector<line> & tmp) {
    const double LARGE = 1e12;
    /* Point A(0, 0), B(LARGE, 0), C(LARGE, LARGE), D(0, LARGE); */
    Point A(-LARGE, -LARGE), B(LARGE, -LARGE), C(LARGE, LARGE), D(-LARGE, LARGE);
    tmp.push_back(line(A, B-A));
    tmp.push_back(line(B, C-B));
    tmp.push_back(line(C, D-C));
    tmp.push_back(line(D, A-D));
}

int main() {
    /* test(); */
    /* freopen("in", "r", stdin); */
    int n, cas = 0;
    while (scanf("%d", &n) == 1 && n) {
        printf("Floor #%d\n", ++cas);
        vector<Point> tmp;
        for (int i = 0; i < n; i++) {
            Point t; t.read();
            tmp.push_back(t);
        }
        vector<line> fp;
        addlarge(fp);
        for (int i = 0; i < n; i++) {
            /* line t(tmp[(i + 1) % n] - tmp[i], tmp[i]); */
            line t(tmp[i], tmp[i] - tmp[(i + 1) % n]);
            fp.push_back(t);
        }
        vector<Point> ans = HalfplaneIntersection(fp);
        if (ans.size() > 0)
            printf("Surveillance is possible.\n\n");
        else
            printf("Surveillance is impossible.\n\n");
    }
    return 0;
}
