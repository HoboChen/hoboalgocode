#include <bits/stdc++.h>

using namespace std;

const int N = 110010;

char str[N << 1], s[N];
int p[N << 1], n, len;

void Manacher(char *str, int *p) {
    int i, id, mx;
    id = mx = 1;
    p[0] = p[1] = 1;
    for (i = 2; i < n; i++) {
        p[i] = 1;
        if (mx > i)
            p[i] = min(p[(id << 1) - i], mx - i);
        while (str[i + p[i]] == str[i - p[i]])
            p[i]++;
        if (i + p[i] > mx) {
            id = i;
            mx = i + p[i];
        }
    }
}

void getstr(char *s) {
    int i;
    str[0] = '$'; str[1] = '#';
    for(i = 0; i < len; i++) {
        str[(i << 1) + 2] = s[i];
        str[(i << 1) + 3] = '#';
    }
    str[n] = 0;
}

int main() {
    int i, ans;
    while(~scanf("%s", s)) {
        len = strlen(s);
        n = len * 2 + 2;
        getstr(s);
        Manacher(str,p);
        ans = 1;
        for(i = 2; i < n; i++) ans = max(ans, p[i] - 1);
        printf("%d\n", ans);
        getchar();
        getchar();
    }
    return 0;
}
