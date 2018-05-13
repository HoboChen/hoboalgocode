
inline int lowbit(x) { return x & -x; }

int sum(int x) {
    long long ret = 0;
    while (x > 0) {
        ret += C[x];
        x -= lowbit(x);
    }
    return ret;
}

void add(int x, int d, int n) {
    while (x <= n) {
        C[x] += d;
        x += lowbit(x);
    }
}
