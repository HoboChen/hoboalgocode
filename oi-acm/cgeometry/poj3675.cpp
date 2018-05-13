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

#define pr(x) cout << #x << " = " << x  << " $";
#define pn cout << endl;

const double PI = 3.1415926535897932384626434;
const double eps = 1e-9; //square of the accuracy

#define Vector Point

inline int sign(double a) { return a < -eps ? -1 : a > eps; }
inline double hypot(double a, double b) { return sqrt(a * a + b * b); }
struct Point {
    double x,y;

    Point(double x = 0, double y = 0): x(x), y(y) {}
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
    bool operator == (const Point & p) const { return sign(x - p.x) == 0 && sign(y - p.y) == 0; }
    double dot(const Point &p) const {return x*p.x + y*p.y;}
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
    //clockwise
    Point rotAlpla(const double &alpha,const Point &o = Point(0,0)) const {
        double nx = cos(alpha)*(x-o.x)+sin(alpha)*(y-o.y);
        double ny = -sin(alpha)*(x-o.x)+cos(alpha)*(y-o.y);
        return Point(nx,ny)+o;
    }
    Point rot90() const {return Point(-y, x);}
    Point unit() {return *this/abs();}

    double abs() {return hypot(x, y);}
    double abs2() {return x*x+y*y;}
    void testWrite () {cout<<"("<<x<<","<<y<<")"<<endl;}
    double getrad() { // return [0, 2pi)
        double res = atan2(y, x);
        if (res < 0) res += 2 * PI;
        if (fabs(res - 2 * PI) < 1e-10) return 0;
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
    return min(fabs(a-b), 2*PI-fabs(a-b));
}

//顺时针或逆时针传入一个凸多边形，返回被半平面q1q2逆时针方向切割掉之后的凸多边形
vector<Point> convexCut (const vector<Point> & ps,Point q1,Point q2) {
    vector<Point> qs;
    int n = ps.size();
    for (int i = 0; i < n; i++) {
        Point p1 = ps[i], p2=ps[(i + 1) % n];
        int d1 = crossOp(q1, q2, p1), d2 = crossOp(q1, q2, p2);
        if (d1 >= 0)
            qs.push_back(p1);
        if (d1 * d2 < 0)
            qs.push_back(lineLineIntersect(p1, p2, q1, q2));
    }
    return qs;
}

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

//判断点p在线段q1q2上，端点重合返回true
bool onSegment(Point p,Point q1,Point q2) {
    return crossOp(q1,q2,p) == 0 && sign((p-q1).dot(p-q2)) <=0 ;
}

//判断线段p1p2和q1q2是否严格相交，重合或端点相交返回false
bool isIntersect (Point p1,Point p2,Point q1,Point q2) {
    return crossOp(p1,p2,q1)*cross(p1,p2,q2) <0 && crossOp(q1,q2,p1)*cross(q1,q2,p2) <0 ;
}

//判断直线p1p2和q1q2是否垂直
bool isVertical(Point p1, Point p2, Point q1, Point q2) {
    return sign((p2-p1).det(q2-q1)) == 0;
}

//点p到直线uv的距离
double distPointToLine(Point p, Point u, Point v) {
    return abs((u-p).det(v-p)) / u.distTo(v);
}

//点p到线段uv的距离
double distPointToSegment(Point p, Point u, Point v) {
    if ((u - v).abs() < eps) return (p-u).abs();
    Vector v1 = u - v, v2 = p - u, v3 = p - v;
    if (sign(v1.dot(v2)) < 0) return v2.abs();
    else if (sign(v1.dot(v3)) > 0) return v3.abs();
    else return fabs(v1.det(v2)) / v1.abs();
}

//判断点q是否在简单多边形p内部，边界返回false
int inPoly(Point q, vector<Point> &p) {
    int n = p.size();
    for (int i=0;i<n;i++) {
        if (onSegment(q,p[i],p[(i+1)%n])) return false;
    }
    Point q2;
    double offsite = 1e10 ;
    for (;;) {
        int flag = true;
        int rnd = rand()%10000;
        q2.x = cos((double)rnd)*offsite;
        q2.y = sin((double)rnd)*offsite;
        for (int i=0; i<n; ++i) {
            if (onSegment(p[i], q, q2)) {
                flag = false;
                break;
            }
            if (flag) break;
        }
    }
    int cnt = 0;
    for (int i=0;i<n;i++) {
        cnt += isIntersect(p[i],p[(i+1)%n],q,q2);
    }
    return cnt & 1;
}

// int inPoly(Point q, vector<Point> & p) {
//  int w = 0;
//  int n = v.size();
//  for (int i = 0; i < n; i++) {
//      if (onSegment(q, p[i], p[(i + 1) % n])) return -1; // on the border
//      int k = sign((p[(i + 1) % n] - p[i]).det(q - p[i]));
//      int d1 = sign(p[i].y - q.y);
//      int d2 = sign(p[(i + 1) % n].y - q.y);
//      if (k > 0 && d1 <= 0 && d2 > 0) wn++;
//      if (k < 0 && d2 <= 0 && d1 > 0) wn--;
//  }
//  if (wn != 0) return 1; // inside
//  return 0; // outside
// }

//直线l1l2是否和圆相交，相切返回true
bool isInterLinCir(Point c,double r,Point l1,Point l2) {
    return (distPointToLine(c,l1,l2)-r) <= 0 ;
}
//圆和线段是否有公共点，线段在圆内部返回true
bool isInterSegCir(Point c,double r,Point p1,Point p2) {
    if ((distPointToLine(c,p1,p2)-r)>0) return false;
    if (sign(c.distTo(p1)-r)<=0 || sign(c.distTo(p2)-r) <= 0) return true;
    Point c2 = (p2-p1).rot90()+c;
    return crossOp(c,c2,p1)*crossOp(c,c2,p2)<=0;
}
//判断圆和圆是否相交，外切或内切返回true
bool isInterCirCir(Point c1,double r1,Point c2,double r2) {
    double dis = c1.distTo(c2);
    return sign(dis-fabs(r1-r2))>=2 && sign(dis-(r1+r2)) <=0;
}
//求直线与圆的交点
int interLinCir(Point c,double r,Point l1,Point l2,Point &p1,Point &p2) {
    if (!isInterLinCir(c, r, l1, l2)) return 0;
    Point c2 = c + (l2-l1).rot90();
    c2 = lineLineIntersect(c,c2,l1,l2);
    double t = sqrt(r*r-(c2-c).abs2());
    p1 = c2+(l2-l1).unit()*t;
    p2 = c2-(l2-l1).unit()*t;
    if (sign(t) == 0) return 1;
    else return 2;
}
//求圆与圆交点
void interCirCir(Point c1,double r1,Point c2,double r2,Point &p1,Point &p2) {
    double t = (1+(r1*r1-r2*r2)/(c1-c2).abs2()) /2;
    Point u = c1+(c2-c1)*t;
    Point v = u+(c2-c1).rot90();
    interLinCir(c1,r1,u,v,p1,p2);
}

inline Point getCirPoint(Point c, double r, double rd) {
    return Point(c.x + r * cos(rd), c.y + r * sin(rd));
}

// cir and cir
int getTangents(Point c1, double r1, Point c2, double r2, Point* a, Point* b) {
    int cnt = 0;
    if (r1 < r2) {swap(c1, c2); swap(r1, r2); swap(a, b);}
    double d2 = (c1-c2).abs2();
    double rdiff = r1 - r2, rsum = r1 + r2;
    if (d2 < rdiff * rdiff) return 0; // neihan

    double base = atan2(c2.y - c1.y, c2.x - c1.x);
    if (sign(d2) == 0 && sign(r1-r2) == 0) return -1;

    if (sign(d2 - rdiff * rdiff) == 0) { // neiqie
        a[cnt] = getCirPoint(c1, r1, base);b[cnt] = getCirPoint(c2, r2, base);
        return 1;
    }
    // there is outter common tagent
    double ang = acos((r1 - r2) / sqrt(d2));
    a[cnt] = getCirPoint(c1, r1, base + ang);
    b[cnt] = getCirPoint(c2, r2, base + ang);
    cnt++;
    a[cnt] = getCirPoint(c1, r1, base - ang);
    b[cnt] = getCirPoint(c1, r1, base - ang);
    cnt++;
    if (sign(d2 - rsum * rsum) == 0) {
        a[cnt] = getCirPoint(c1, r1, base);b[cnt] = getCirPoint(c2, r2, base + PI);cnt++;
    }
    else if (d2 > rsum * rsum) {
        double ang = acos((r1 + r2) / sqrt(d2));
        a[cnt] = getCirPoint(c1, r1, base + ang);
        b[cnt] = getCirPoint(c2, r2, PI + base + ang);
        cnt++;
        a[cnt] = getCirPoint(c1, r1, base - ang);
        b[cnt] = getCirPoint(c1, r1, PI + base - ang);
        cnt++;
    }
    return cnt;
}

Point centerCirOut(const Point &a, const Point &b, const Point &c) {
    double a1=b.x-a.x, b1=b.y-a.y, c1=(a1*a1+b1*b1)/2;
    double a2=c.x-a.x, b2=c.y-a.y, c2=(a2*a2+b2*b2)/2;
    double d=a1*b2-a2*b1;
    return Point(a.x + (c1*b2-c2*b1)/d, a.y + (a1*c2-a2*c1)/d);
}

bool isPointInCir(Point c, double r, Point p) {
    return sign((p - c).abs2() - r * r) <= 0;
}

struct Circle {
    double r;
    Point c;
    Circle() {}
    Circle(Point a, double b): c(a), r(b) {}
    Point getPoint(double a) { return Point(c.x + cos(a) * r, c.y + sin(a) * r); }
};

bool isPointInCir(Point P, Circle C) {
    return sign((C.c - P).abs() - C.r) <= 0;
}

double Angle(Vector a, Vector b) {
    if (sign(a.abs2()) == 0 || sign(b.abs2()) == 0 || sign((a-b).abs2() == 0))
        return 0;
    return acos(max((double)-1, min((double)1, a.dot(b) / a.abs() / b.abs())));
}

double Cross(const Vector& a, const Vector& b) {
    return a.x * b.y - a.y * b.x;
}

double Area2(Point A,Point B,Point C) {return Cross(B-A,C-A);}

Point GetLineProjection(Point p,Point A,Point B) {
    Vector v=B-A;
    return A+v*(v.dot(p-A))/(v.dot(v));
}

struct Line{
    Point p;
    Vector v;
    double ang;
    Line(){}
    Line(Point p, Vector v):p(p),v(v) {ang=atan2(v.y,v.x); }
    bool operator<(const Line & L) const {
        return ang<L.ang;
    }
    Point getPoint(double a) {
        return p + v*a;
    }
};

int getSegCircleIntersection(Line L,Circle cir,vector<Point> & sol) {
    if (sign(distPointToLine(cir.c,L.p,L.p+L.v)-cir.r)==0) {
        Point A= GetLineProjection(cir.c,L.p,L.p+L.v);
        if (onSegment(A,L.p,L.p+L.v) || L.p==A || L.p+L.v==A  )
            sol.push_back(A);
        return sol.size();
    }
    double t1,t2;
    double a = L.v.x, b = L.p.x - cir.c.x, c = L.v.y, d= L.p.y - cir.c.y;
    double e = a*a+c*c, f = 2*(a*b + c*d), g = b*b+d*d-cir.r*cir.r;
    double delta = f*f - 4*e*g;
    if (sign(delta)<0) return 0;
    else if (sign(delta)==0) {
        t1 = -f / (2*e);
        if (sign(t1)>=0&&sign(t1-1)<=0) {
            sol.push_back(L.getPoint(t1));
        }
        return sol.size();
    }
    t1 = (-f - sqrt(delta)) / (2*e); if (sign(t1)>=0&&sign(t1-1)<=0) sol.push_back(L.getPoint(t1));
    t2 = (-f + sqrt(delta)) / (2*e); if (sign(t2)>=0&&sign(t2-1)<=0) sol.push_back(L.getPoint(t2));
    if(sol.size()==2 && t1>t2) swap(sol[1],sol[0]);
    return sol.size();
}
double areaPolyCirX(vector<Point> & p, Circle c) {
    int n = p.size();
    double m = c.r, ans = 0;
    Point O = Point();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        bool b = isPointInCir(p[i], c);
        bool b2 = isPointInCir(p[j], c);
        double opr;
        Point A = p[i], B = p[j];
        if (sign(Area2(O,A,B))>=0) opr=1; else opr=-1;
        if (b&&b2) {
            ans+=opr*fabs(Area2(A,B,O))/2;
        } else if (!b&&!b2){
            Line l=Line(A,B-A);
            vector<Point> sol;
            getSegCircleIntersection(l,c,sol);
            if (sol.size()==2) {
                ans+=opr*fabs(Area2(sol[0],sol[1],O))/2;
                ans+=opr*m*m/2*(Angle(A,sol[0])+Angle(sol[1],B));
            } else {
                ans+=opr*m*m/2*(Angle(A,B));
            }
        } else {
            Line l=Line(A,B-A);
            vector<Point> sol;
            getSegCircleIntersection(l,c,sol);
            if (sol.size()==2) {
                ans+=opr*fabs(Area2(sol[0],sol[1],O))/2;
                ans+=opr*m*m/2*(Angle(A,sol[0])+Angle(sol[1],B));
            } else if(b) {
                ans+=opr*fabs(Area2(sol[0],A,O))/2;
                ans+=opr*m*m/2*(Angle(sol[0],B));
            } else {
                ans+=opr*fabs(Area2(sol[0],B,O))/2;
                ans+=opr*m*m/2*(Angle(sol[0],A));
            }
        }
    }
    ans=fabs(ans);
    return ans;
}

int main() {
    double R;
    while (~scanf("%lf", &R)) {
        int n;
        scanf("%d", &n);
        vector<Point> P;
        Circle c = Circle(Point(), R);
        for (int i = 0; i < n; i++) {
            Point t;
            t.read();
            P.push_back(t);
        }
        printf("%.2f\n", areaPolyCirX(P, c));
    }
    return 0;
}
