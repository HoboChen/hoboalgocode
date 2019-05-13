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

const int maxn = 200000 + 10000;
const double eps = 1e-10;

int st[maxn][25], n, a[maxn];

void getST(int * a, int n) {
    int m = log(n) / log(2);
    for (int i = 1; i <= n; i++)
        st[i][0] = a[i];
    for (int j = 1; j <= m; j++)
        for (int i = n; i > 0; i--) {
            st[i][j] = st[i][j - 1];
            if (i + (1 << (j - 1)) <= n)
                st[i][j] = max(st[i][j], st[i + (1 << (j - 1))][j - 1]);
    }
}

int query(int l, int r) {
    if (l > r) return -1;
    int k = log(r - l + 1) / log(2);
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

int q[maxn], lpos[maxn], rpos[maxn];

int main() {
     int n;
     while (scanf("%d", &n) == 1 && n) {
         int qe;
         scanf("%d", &qe);
         for (int i = 1; i <= n; i++)
             scanf("%d", &q[i]);
         int cnt = 1;
         for (int i = 1; i <= n; i++) {
             lpos[cnt] = i;
             while (q[i] == q[i + 1]) i++;
             rpos[cnt] = i;
             a[cnt] = rpos[cnt] - lpos[cnt] + 1; 
             cnt++;
         }
         cnt--;
         getST(a, cnt);
         int l, r;
         for (int i = 0; i < qe; i++) {
             scanf("%d%d", &l, &r);
             if (l == r) {
             	printf("1\n");
             	continue;
             }
             int cl = lower_bound(lpos + 1, lpos + cnt + 1, l) - lpos;
             int cr = lower_bound(rpos + 1, rpos + cnt + 1, r) - rpos;
             cl = max(cl - 1, 1);
             int ans = -1;
             int le = 0, re = 0;
             if (cl != cr) {
	             if (l > lpos[cl]) {
	                 le = rpos[cl] - l + 1;
	                 cl++;
	             }
	             if (r < rpos[cr]) {
	                 re = r - rpos[cr - 1];
	                 cr--;
	             }
             }
             else {
             	le = re = r - l + 1;
             	cr--;
             }
             int t = query(cl, cr);
             ans = max(ans, t);
             ans = max(ans, le);
             ans = max(ans, re);
             printf("%d\n", ans);
         }
    }
    return 0;
}
