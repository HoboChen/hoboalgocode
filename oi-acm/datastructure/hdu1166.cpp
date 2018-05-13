#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int maxn = 50000 + 10000;
const double eps = 1e-10;

inline int lowbit(int x) { return x & -x; }

int c[maxn];

int sum(int x) {
    int ret = 0;
    while (x > 0) {
        ret += c[x];
        x -= lowbit(x);
    }
    return ret;
}

int n;

void add(int x, int d) {
    while (x <= n) {
        c[x] += d;
        x += lowbit(x);
    }
}

char buf[100];

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        memset(c, 0, sizeof(c));
        scanf("%d", &n);
        for (int j = 1; j <= n; j++) {
            int tmp;
            scanf("%d", &tmp);
            add(j, tmp);
        }
        char t;
        scanf("%c", &t);
        printf("Case %d:\n", i);
        while (1) {
            gets(buf);
            char op[50];
            int t1, t2;
            sscanf(buf, "%s", op);
            if (op[0] == 'E') break;
            sscanf(buf, "%s%d%d", op, &t1, &t2);
            if (op[0] == 'Q')
                printf("%d\n", sum(t2) - sum(t1 - 1));
            if (op[0] == 'S')
                add(t1, -t2);
            if (op[0] == 'A')
                add(t1, t2);
        }
    }
    return 0;
}
