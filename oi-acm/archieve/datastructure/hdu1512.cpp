#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;
using namespace __gnu_cxx;

#ifdef ONLINE_JUDGE
#define fio 0
#else
#define fio 1
#endif

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;
inline void px(string s) { cout << s << ends; }

const int maxn = 100000 + 10000;
const int inf = 0x3e3e3e3e;
const long long llinf = (long long)0x3e3e3e3e * 0x3e3e3e3e;

const double eps = 1e-10;

int p[maxn];

int find(int x, int *p) { return p[x] == x ? x : p[x] = find(p[x], p); }

void merge(int i, int j, int *p) {
    int x = find(i, p), y = find(j, p);
    if (x < y) p[y] = x;
    else p[x] = y;
}

void init(int * p, int n) {
    for (int i = 1; i <= n; i++)
        p[i] = i;
}

int n, m;
int strong[maxn];

// 624ms, 35852kb
/* __gnu_pbds::priority_queue<int, less<int>, __gnu_pbds::thin_heap_tag> pq[maxn]; */
// 448ms, 7080kb
/* __gnu_pbds::priority_queue<int, less<int>, __gnu_pbds::pairing_heap_tag> pq[maxn]; */
// 556ms, 7468kb
/* __gnu_pbds::priority_queue<int, less<int>, __gnu_pbds::binomial_heap_tag> pq[maxn]; */
// 448ms, 21656kb
__gnu_pbds::priority_queue<int, less<int>, __gnu_pbds::rc_binomial_heap_tag> pq[maxn];
// TLE
/* __gnu_pbds::priority_queue<int, less<int>, __gnu_pbds::binary_heap_tag> pq[maxn]; */

template<typename _t>
void containerprint(const _t & val)  {
    for (auto i = val.begin(); i != val.end(); i++)
        cout << *i << " $";
    cout << endl;
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        init(p, n);
        for (int i = 1; i <= n; i++) pq[i].clear();
        for (int i = 1; i <= n; i++) {
            scanf("%d", &strong[i]);
            pq[i].push(strong[i]);
        }
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            int t1, t2;
            scanf("%d%d", &t1, &t2);
            if (find(t1, p) == find(t2, p)) {
                printf("%d\n", -1);
                continue;
            }
            else {
                int f1 = find(t1, p), f2 = find(t2, p);
                merge(t1, t2, p);
                if (f1 > f2) swap(f1, f2);
                int mxt1 = pq[f1].top(), mxt2 = pq[f2].top();
                pq[f1].pop(); pq[f2].pop();
                pq[f1].push(mxt1 / 2); pq[f2].push(mxt2 / 2);
                pq[f1].join(pq[f2]);
                printf("%d\n", pq[f1].top());
            }
        }
    }
    return 0;
}
