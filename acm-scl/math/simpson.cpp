#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <string>
#include <cstring>

using namespace std;

const int maxn = 0;
const double eps = 1e-6;

#define pr(x) cout << #x << " = " << x << "$ ";
#define ll long long

double a, b, x, y;

double F(double x) {
    return sqrt((1 - pow(x / a, 2)) * b * b);
}

double simpson(double a, double b){
    double c = a + (b - a) / 2.0;
    return (F(a) + 4 * F(c) + F(b)) * (b-a) / 6.0;
}

double asr(double a, double b, double eps, double A) {
    double c = a + (b - a) / 2.0;
    double L = simpson(a, c), R = simpson(c, b);
    if (fabs(A - L - R) < 15 * eps) return L + R + (A - L - R) / 15;
    return asr(a, c, eps / 2.0, L) + asr(c, b, eps / 2.0, R);
}

double asr(double a, double b, double eps) {
    return asr(a, b, eps, simpson(a, b));
}

int main() {
    int kase;
    cin >> kase;
    for (int i = 0; i < kase; i++) {
        // printf("Case #%d: ",i+1);    
        scanf("%lf%lf%lf%lf", &a, &b, &x, &y);
        double ans = asr(x, y, eps);
        ans *= 2.0;
        printf("%.3lf\n", ans);
    }
    return 0;
}
