#include <bits/stdc++.h>

using namespace std;

const double inf = 1e20;
const int maxn = 100000 + 10000;

struct Point {
    double x,y;
    Point() {}
    Point(double x,double y): x(x), y(y) {}

    Point operator + (const Point &p) const {return Point(x+p.x,y+p.y);}
    Point operator - (const Point &p) const {return Point(x-p.x,y-p.y);}
    Point operator * (double res) const {return Point(x*res,y*res);}
    Point operator / (double res) const {return Point(x/res,y/res);}

    double abs() {return hypot(x,y);}
    double abs2() {return x*x+y*y;}
};

Point p[maxn];
int n, t[maxn];

bool cmpxy(const Point& a, const Point& b) {
    if(a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}

bool cmpy(const int& a, const int& b) {
    return p[a].y < p[b].y;
}

double dis(int i, int j) {
    return (p[i]-p[j]).abs();
}

double Closest_Pair(int left, int right) {
    double res = inf;
    if(left == right)
        return res;
    if(left + 1 == right)
        return dis(left, right);
    int mid = (left + right) / 2;
    double d1 = Closest_Pair(left, mid);
    double d2 = Closest_Pair(mid + 1, right);
    res = min(d1, d2);
    int i, j, k = 0;
    for(i = left; i <= right; i++) {
        if(fabs(p[mid].x - p[i].x) <= res)
            t[k++] = i;
    }
    sort(t, t+k, cmpy);
    for(i = 0; i < k; i++) {
        for(j = i + 1; j < k && p[t[j]].y-p[t[i]].y < res; j++) {
            double tmp = dis(t[i],t[j]);
            res = min(res, tmp);
        }
    }
    return res;
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        for(int i = 0; i < n; i++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        sort(p, p+n, cmpxy);
        printf("%.2lf\n",Closest_Pair(0, n - 1) / 2.0);
    }
    return 0;
}
