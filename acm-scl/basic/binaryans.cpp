#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define fio 0
#else
#define fio 1
#endif

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;
inline void px(string s) { cout << s << ends; }

const int maxn = 1000;
const int inf = 0x3e3e3e3e;
const long long llinf = (long long)0x3e3e3e3e * 0x3e3e3e3e;

const double eps = 1e-10;

int a[maxn] = {-1, 1, 2, 3, 3, 4, 5};

int tar;

bool check(int i, int * a) { // if use a[i] < tar, return x - 1; else return the most right x
    return a[i] <= tar;
}

int binaryfind(int tarx, int ll, int rr, int * a) { // find tarx, in [ll, rr), in int a[]
    tar = tarx;
    int l = ll - 1, r = rr, mid, ans;
    while (l < r) {
        mid = l + (r - l) / 2;
        if (check(mid, a)) {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid;
    }
    return ans;
}

int main() {
    if (fio) freopen("in", "r", stdin);

    return 0;
}
