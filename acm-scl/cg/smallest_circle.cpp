#include <bits/stdc++.h>

using namespace std;

#define Vector Point
const double EPS = 1e-12; //square of the accuracy
inline int sign(double a) {
    return a < -EPS ? -1 : a > EPS;
}

struct Point {
    double x,y;
    Point() {}
    Point(double x,double y): x(x), y(y) {}

    Point operator + (const Point &p) const {return Point(x+p.x,y+p.y);}
    Point operator - (const Point &p) const {return Point(x-p.x,y-p.y);}
    Point operator * (double d) const {return Point(x*d,y*d);}
    Point operator / (double d) const {return Point(x/d,y/d);}

    double abs() {return hypot(x,y);}
    double abs2() {return x*x+y*y;}
};

Point centerCirOut(const Point &a, const Point &b, const Point &c) {
    double a1=b.x-a.x, b1=b.y-a.y, c1=(a1*a1+b1*b1)/2;  
    double a2=c.x-a.x, b2=c.y-a.y, c2=(a2*a2+b2*b2)/2;  
    double d=a1*b2-a2*b1;  
    return Point(a.x + (c1*b2-c2*b1)/d, a.y + (a1*c2-a2*c1)/d);   
}

bool isPointInCir(Point c, double r, Point p) {
    return sign((p - c).abs2() - r * r) <= 0;
}

const int maxn = 1000;

/* int N; */
Point stu[maxn];
Point oxc;
double oxr;

void init(int N) {
    for (int i = 0; i < N; i++) 
        scanf("%lf%lf", &stu[i].x, &stu[i].y);
}

void solve(Point* stu, int N, Point& oxc, double& oxr ) {
    random_shuffle(stu, stu + N);
    Point res = stu[0];
    double resr = 0;
    for (int i = 1 ; i < N; i++) {
        if (!isPointInCir(res, resr, stu[i])) {
            res = (stu[i] + stu[0]) / 2;
            resr = (res - stu[0]).abs();
            for (int j = 1; j < i; j++) {
                if (!isPointInCir(res, resr, stu[j])) {
                    res = (stu[i] + stu[j]) / 2;
                    resr = (res - stu[j]).abs();
                    for (int k = 1; k < j; k++) {
                        if (!isPointInCir(res, resr, stu[k])) {
                            res = centerCirOut(stu[i], stu[j], stu[k]);
                            resr = (res - stu[i]).abs();
                        }
                    }
                }
            }
        }
    }
    oxc = res;
    oxr = resr;
}



int main () {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        init(n);
        solve(stu, n, oxc, oxr);
        printf("%.2lf %.2lf %.2lf\n", oxc.x, oxc.y, oxr);
    }
    return 0;
}

