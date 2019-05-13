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

#define pr(x) cout << #x << " = " << x << " $ ";
#define pn cout << endl;
#define N 50000

#define EPS eps
#define Vector Point
const double eps = 1e-10; //square of the accuracy
inline int sign(double a) {
	return a < -EPS ? -1 : a > EPS;
}

const double M_PI = 3.141592653589793238462643383;

struct Point {
	double x,y;
	Point() {}
	Point(double x,double y): x(x), y(y) {}
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
	double det(const Point &p) {return x*p.y - y*p.x;}
	double alpha() const {return atan2(y,x);} //return [-pi,pi]
	double distTo(const Point &p) const {
		double dx=x-p.x, dy=y-p.y;
		return hypot(dx,dy);
	}
	double alphaTo(const Point &p) const {
		double dx=x-p.x, dy=y-p.y;
		return atan2(dy,dx);
	}
	//clockwise
	Point rotAlpla(const double &alpha,const Point &o = Point(0,0)) const {
		double nx = cos(alpha)*(x-o.x)+sin(alpha)*(y-o.y);
		double ny = -sin(alpha)*(x-o.x)+cos(alpha)*(y-o.y);
		return Point(nx,ny)+o;
	}
	Point rot90() const {return Point(-y, x);}
	Point unit() {return *this/abs();}
	
	double abs() {return hypot(x,y);}
	double abs2() {return x*x+y*y;}
	void testWrite () {cout<<"("<<x<<","<<y<<")"<<endl;}
	double getrad() { // return [0, 2pi)
		double res = atan2(y, x);
		if (res < 0) res += 2 * M_PI;
		if (fabs(res - 2 * M_PI) < 1e-10) return 0;
		return res;
	}

	void read() {scanf("%lf%lf",&x,&y);}
	void write() {printf("%lf %lf ", x, y);}
};

#define cross(p1,p2,p3) ((p2.x-p1.x) * (p3.y-p1.y) - (p3.x-p1.x) * (p2.y-p1.y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))

// ensure that two lines are not in coincidence
Point lineLineIntersect(Point p1, Point p2, Point q1, Point q2) {
	double a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return (p1 * a2 + p2 * a1) / (a1 + a2);
}
double minDiff(double a,double b) { //a,b in [0,2pi)
	return min(fabs(a-b), 2*M_PI-fabs(a-b));
}

//凸包
vector<Point> convexHull(vector<Point> ps) {
	int n = ps.size();
	if (n<=1)
		return ps;
	sort(ps.begin(),ps.end());
	vector<Point> qs;
	for (int i=0; i<n; qs.push_back(ps[i++])) {
		while (qs.size() > 1 && crossOp(qs[qs.size()-2], qs.back(), ps[i]) <= 0)
			qs.pop_back();
	}
	for (int i = n - 2, t = qs.size(); i >= 0; qs.push_back(ps[i--])) {
		while ((int)qs.size() > t && crossOp(qs[(int)qs.size()-2], qs.back(), ps[i]) <=0 )
			qs.pop_back();
	}
	qs.pop_back();
	return qs;
}


//凸包直径
double convexDiameter (const vector<Point> &ps) {
	int n = ps.size();
	int is = 0,js =0;
	for (int i=1;i<n;i++) {
		if (ps[i].x>ps[is].x)
			is = i;
		if (ps[i].x<ps[js].x)
			js = i;
	}
	double maxd = ps[is].distTo(ps[js]);
	int i = is, j = js;
	do {
		if ((ps[(i + 1) % n] - ps[i]).det(ps[(j + 1) % n] - ps[j]) >= 0)
			(++j) %= n;
		else 
			(++i) %= n;
		maxd = max(maxd, ps[i].distTo(ps[j]));
	} while (i != is || j != js);
	return maxd;
}

double distPointToLine(Point p, Point u, Point v) {
    return abs((u-p).det(v-p)) / u.distTo(v);
}

double calc(const vector<Point> & P) {
    double ret = 1e10, tmp;
    int s = P.size();
    for (int i = 0; i < s; i++) {
        tmp = -1;
        for (int j = 0; j < s; j++) {
            tmp = max(distPointToLine(P[j], P[i], P[(i + 1) % s]), tmp);
        }
        ret = min(ret, tmp);
    }
    return ret;
}

Point p[N]; 

int main() {	
	int k, n;  
    Point t, cir;  
    double d, r;  
    while (cin >> cir.x >> cir.y >> r) {  
        k = 0;  
        if (r < 0) break;  
        cin >> n;  
        for(int i = 0; i < n; i++) {  
            t.read();
            d = (t - cir).abs2();
            if(d < r * r || fabs(d - r * r) < eps) {  
                p[k].x = t.x;  
                p[k].y = t.y;  
                k++;  
            }  
        }  
        int maxval = 0;  
        for(int i = 0; i < k; i++) {  
            int count = 1;  
            for(int j = 0; j < k; j++) {  
                if(i != j && cross(cir, p[i], p[j]) >= 0)  
                    count++;  
            }  
            if (count > maxval) maxval = count;  
        }  
        cout << maxval << endl;  
    }  
    return 0;
}

