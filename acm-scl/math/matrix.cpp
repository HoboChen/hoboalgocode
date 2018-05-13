// xdu 1145

#include <bits/stdc++.h>

using namespace std;

const int maxm = 3;

const long long mod = 1000000007;
const long long rev = 500000004;

template<typename _t>
struct Ma {
    int n;
    _t a[maxm][maxm];

    Ma () { }
    Ma (const Ma & b) {
        for (int i = 0; i < b.n; i++)
            for (int j = 0; j < b.n; j++)
                a[i][j] = b.a[i][j];
        n = b.n;
    }

    Ma (const _t b[][maxm], int size) {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                a[i][j] = b[i][j];
        n = size;
    }

    static Ma getUnit(int n) {
        _t t[maxm][maxm];
        memset(t, 0, sizeof(t));
        for (int i = 0; i < n; i++)
            t[i][i] = 1;
        return Ma(t, n);
    }

    Ma operator +  (const Ma & b) {
        if (b.n != n) return getUnit(1);
        _t t[maxm][maxm];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                t[i][j] = a[i][j] + b.a[i][j];
        return Ma(t, n);
    }

    Ma operator * (const Ma & b) {
        if (b.n != n) return getUnit(1);
        _t t[maxm][maxm];
        memset(t, 0, sizeof(t));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++) {
                    // t[i][j] += a[i][k] * b.a[k][j];
                    t[i][j] += (unsigned long long) a[i][k] * b.a[k][j] % mod;
                    t[i][j] %= mod;
                }
        return Ma(t, n);
    }

    void print() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                printf("%d ", a[i][j]);
            printf("\n");
        }
    }
};

Ma<long long> hobo;

Ma<long long> pow(Ma<long long> k, unsigned long long n) {
    if (n == 0) return Ma<long long>::getUnit(3);
    if (n == 1) return k;
    Ma<long long> tmp = pow(k, n / 2);
    if (n % 2 == 0){
        return tmp * tmp;
    }
    else
        return tmp * tmp * k;
}

void powx(Ma<long long> k, unsigned long long n) {
    Ma<long long> tmp(k);
    Ma<long long> ans = Ma<long long>::getUnit(3);
    while (n != 0) {
        if (n % 2 == 1) ans = ans * tmp;
        tmp = tmp * tmp;
        n /= 2;
    }
    hobo = ans;
    return;
}

long long h(unsigned long long d) {
    long long t[3][3] = {1, 1, 1,
        1, 0, 0,
        0, 1, 0};
    hobo = Ma<long long>(t, 3);
    hobo = pow(hobo, d);
    // powx(hobo, d);
    long long res = ((unsigned long long)hobo.a[2][0] + hobo.a[2][1] + hobo.a[2][2]) % mod;
    return res;
}

long long f(unsigned long long d) {
    if (d == 0) return 0;
    long long t1 = h(d + 3);
    long long t2 = h(d + 1);
    long long ans = ((unsigned long long) t1 - t2 + mod) % mod;
    ans = (unsigned long long) ans * rev % mod;
    return ans % mod;
}

long long getans(unsigned long long l, unsigned long long r) {
    long long t1 = f(r);
    long long t2 = f(l - 1);
    long long ans = ((unsigned long long)t1 - t2 + mod) % mod;
    return ans;
}

int main() {
    unsigned long long l, r;
    while (cin >> l >> r) {
        if (l == 0 && r == 0) { printf("1\n"); continue; }
        if (l == 1) {
            printf("%d\n", (int)getans(l, r) - 1);
            continue;
        }
        printf("%d\n", (int)getans(l, r));
    }
    return 0;
}

