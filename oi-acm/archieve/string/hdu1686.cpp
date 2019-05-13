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

const int maxn = 100000;
const int inf = 0x3e3e3e3e;
const long long llinf = (long long)0x3e3e3e3e * 0x3e3e3e3e;

const double eps = 1e-10;

/* int find_substring(string & pattern, string & text) { */
int find_substring(char * pattern, int plen, char * text, int tlen) {
    /* int n = pattern.size(), ans = 0; */
    int n = plen, ans = 0;
    vector<int> next(n + 1, 0);
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0) {
            j = next[j];
            if (pattern[j] == pattern[i]) { next[i + 1] = j + 1; break; }
        }
    }
    vector<int> pos;
    /* int m = text.size(); */
    int m = tlen;
    for (int i = 0, j = 0; i < m; i++) {
        if (j < n && text[i] == pattern[j]) j++;
        else {
            while (j > 0) {
                j = next[j];
                if (text[i] == pattern[j]) { j++; break; }
            }
        }
        if (j == n)
            /* pos.push_back(i - n + 1); */
            ans++;
    }
    return ans;
}
const int maxl = 1000000 + 10000;
char a[maxn], b[maxl];

int main() {
    if (fio) freopen("in", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s\n%s", a, b);
        cout << find_substring(a, strlen(a), b, strlen(b)) << endl;
    }
    return 0;
}

