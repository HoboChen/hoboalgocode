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

const int maxnode = 100000;

int lch[maxnode], rch[maxnode], pnt[maxnode];
int data[maxnode], sum[maxnode], mx[maxnode], rev[maxnode], lst[maxnode], total;

inline bool isrot(int t) { return (!pnt[t] || (lch[pnt[t]] != t && rch[pnt[t]] != t)); }

void reverse(int cur) {
    if (!rev[cur]) return;
    swap(lch[cur], rch[cur]);
    rev[lch[cur]] ^= 1;
    rev[rch[cur]] ^= 1;
    rev[cur] = 0;
}

inline void update(int cur) {
    sum[cur] = sum[lch[cur]] + sum[rch[cur]] + data[cur];
    mx[cur] = max(data[cur], max(mx[lch[cur]], mx[rch[cur]]));
};


int main() {
    if (fio) freopen("in", "r", stdin);

    return 0;
}
