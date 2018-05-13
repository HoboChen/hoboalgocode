#include <bits/stdc++.h>

using namespace std;
const int maxn = 40;

unsigned long long hashstr(char *s, int len, int seed = 10007) {
    unsigned long long ret = 0;
    int i = 0;
    for (; i < len; i++)
        if (s[i] == '0') continue;
        else break;
    for (; i < len; i++) {
        ret *= seed;
        ret += s[i];
    }
    return ret;
}

char s[maxn];

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        unordered_map<unsigned long long, int> ans1;
        while (n--) {
            scanf("%s\n", s);
            ans1[hashstr(s, strlen(s))]++;
        }
        int ret1 = 0;
        for (auto i = ans1.begin(); i != ans1.end(); i++)
            ret1 = max(ret1, i -> second);
        cout << ret1 << endl;
    }
    return 0;
}
