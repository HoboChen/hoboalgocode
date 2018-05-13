
#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 1000;
const double eps = 1e-10;

int p[maxn];

int find(int x, int *p) { return p[x] == x ? x : p[x] = find(p[x], p); }

void merge(int i, int j, int *p) {
    int x = find(i, p), y = find(j, p);
    p[y] = x;
}

void init(int * p, int n) {
    for (int i = 1; i <= n; i++)
        p[i] = i;
}

int main() {

    return 0;
}
