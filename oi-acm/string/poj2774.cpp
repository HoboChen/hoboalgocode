
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <deque>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <stack>
#include <deque>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <climits>

#ifdef ONLINE_JUDGE
#define fio 0
#else
#define fio 1
#endif

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;
inline void px(string s) { cout << s << ends; }

const int maxn = 100000 + 10000;
const int inf = 0x3e3e3e3e;
const long long llinf = (long long)0x3e3e3e3e * 0x3e3e3e3e;

const double eps = 1e-10;

char s1[maxn], s2[maxn];
unsigned long long f1[maxn], f2[maxn], pw[maxn];

void get_pow(unsigned long long *f, int len, int seed = 131) {
    f[0] = 1;
    for (int i = 1; i <= len; i++)
        f[i] = f[i - 1] * seed;
}

void cal_hash(unsigned long long *f, char * s, int len, int seed = 131) {
    for (int i = 0; i < len; i++)
        f[i + 1] = f[i] * seed + s[i];
}

unsigned long long get_hash(unsigned long long * h, int l, int r) {
    return h[r] - h[l] * pw[r - l];
}

bool check(int len, int len1, int len2, unsigned long long *f1, unsigned long long *f2) {
    /* if (len < 1) return 1; */
    vector<unsigned long long> tmp;
    for (int i = len; i <= len1; i++)
        tmp.push_back(get_hash(f1, i - len, i));
    sort(tmp.begin(), tmp.end());
    for (int i = len; i <= len2; i++) {
        unsigned long long t = get_hash(f2, i - len, i);
        if (binary_search(tmp.begin(), tmp.end(), t)) return 1;
    }
    return 0;
}

int main() {
    /* if (fio) freopen("in", "r", stdin); */
    scanf("%s", s1);
    scanf("%s", s2);
    int len1 = strlen(s1), len2 = strlen(s2);
    int r = max(len1, len2);
    get_pow(pw, r);
    cal_hash(f1, s1, len1);
    cal_hash(f2, s2, len2);
    int l = 0, mid, ans = 0;
    while (l < r) {
        mid = l + (r - l) / 2;
        if (check(mid + 1, len1, len2, f1, f2)) {
            l = mid + 1;
            ans = l;
        }
        else
            r = mid;
    }
    printf("%d\n", ans);
    return 0;
}
