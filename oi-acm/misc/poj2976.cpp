
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

const int maxn = 10000;
const double eps = 1e-6;

long long a[maxn], b[maxn];
double c[maxn];

int main() {
    int n, k;
    while (scanf("%d%d", &n, &k) == 2 ) {
        if (n == 0 && k == 0) break;
        for (int i = 0; i < n; i++)
            scanf("%lld", &a[i]);
        for (int i = 0; i < n; i++)
            scanf("%lld", &b[i]);
        double l = 0, r = 1 + eps;
        double m = (l + r) / 2;
        while (r - l > eps) {
            m = (l + r) / 2;
            double cur = 0;
            for (int i = 0; i < n; i++)
                c[i] = a[i] - m * b[i];
            sort(c, c + n);
            for (int i = k; i < n; i++) 
                cur += c[i];
            if (cur > 0)
                l = m;
            else 
                r = m;
        }
        printf("%.0f\n", m * 100);
    }
    return 0;
}
