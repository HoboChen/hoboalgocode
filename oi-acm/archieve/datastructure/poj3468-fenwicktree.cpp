
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

const int maxn = 100000 + 10000;
const double eps = 1e-10;

long long c1[maxn], c2[maxn], s[maxn];

inline int lowbit(int x) { return x & -x; }

long long sum(int x, long long * c) {
    long long ret = 0;
    while (x > 0) {
        ret += c[x];
        x -= lowbit(x);
    }
    return ret;
}

void add(int x, int d, long long * c, int n) {
    while (x <= n) {
        c[x] += d;
        x += lowbit(x);
    }
}

inline long long query_delta(int x) {
    long long ret = 0;
    ret += (x + 1) * sum(x, c1);
    ret -= sum(x, c2);
    return ret;
} 

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        int t;
        scanf("%d", &t);
        s[i] = t + s[i - 1];
    }
    for (int i = 0; i < k; i++) {
        getchar();
        char o;
        int l, r;
        scanf("%c%d%d", &o, &l, &r);
        if (o == 'Q') {
            long long ret = 0;
            ret += s[r] - s[l - 1];
            ret += query_delta(r) - query_delta(l - 1);
            printf("%lld\n", ret);
        }
        if (o == 'C') {
            int c;
            scanf("%d", &c);
            add(l, c, c1, n);
            add(r + 1, -c, c1, n);
            add(l, c * l, c2, n);
            add(r + 1, -(c * (r + 1)), c2, n);
        }
    }
    return 0;
}
