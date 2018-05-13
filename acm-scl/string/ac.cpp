#include <bits/stdc++.h>

const int SIGMA_SIZE = 26;
const int maxn = 1000005;

typedef long long LL;

using namespace std;

int ch[maxn][SIGMA_SIZE], val[maxn], f[maxn], cnt, last[maxn];

inline int idx(char c) { return c - 97; }

void insert(char s[]) {
    int len = strlen(s);
    int u = 0;
    for(int i = 0; i < len; i++) {
        int v = idx(s[i]);
        if(!ch[u][v]) {
            ch[u][v] = ++cnt;
            int t = ch[u][v];
            f[t] = val[t] = last[t] = 0;
            memset(ch[t], 0, sizeof(ch[t]));
        }
        u = ch[u][v];
    }
    val[u] = len;
}

int sum[maxn];

void find(char T[]) {
    int n = strlen(T);
    int j = 0;
    for(int i = 0; i < n; i++) {
        int c = idx(T[i]);
        j = ch[j][c];
        if (val[j]) {
            sum[i + 1]--;
            sum[i - val[j] + 1]++;
        }
        else {
            int tmp = last[j];
            while (tmp) {
                sum[i + 1]--;
                sum[i - val[tmp] + 1]++;
                tmp = last[tmp];
            }
        }
    }
}

int q[maxn * SIGMA_SIZE];

void getFail() {
    int L = 0, R = 0;
    f[0] = 0;
    for(int c = 0; c < SIGMA_SIZE; c++) {
        int u = ch[0][c];
        if(u) {
            f[u] = 0;
            q[R++] = u;
            last[u] = 0;
        }
    }
    while(L < R) {
        int r = q[L++];
        for(int c = 0; c < SIGMA_SIZE; c++) {
            int u = ch[r][c];
            if(!u) { ch[r][c] = ch[f[r]][c]; continue; }
            q[R++] = u;
            int v = f[r];
            while(v && !ch[v][c]) v = f[v];
            f[u] = ch[v][c];
            last[u] = val[f[u]] ? f[u] : last[f[u]];
        }
    }
}

inline void init() {
    cnt = 0;
    memset(ch[0], 0, sizeof(ch[0]));
    f[0] = val[0] = 0;
}

char ss[maxn], tt[maxn];

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        init();
        int n;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%s", ss);
            insert(ss);
        }
        getFail();
        gets(ss);
        gets(ss);
        int len = strlen(ss);
        for(int i = 0; i < len; i++) sum[i] = 0;
        for(int i = 0; i < len; i++)
            tt[i] = tolower(ss[i]);
        tt[len] = 0;
        find(tt);
        LL S = 0;
        for(int i = 0; i < len; i++) {
            S += sum[i];
            if(S > 0) putchar('*');
            else putchar(ss[i]);
        }
        printf("\n");
    }
    return 0;
}
