#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000;

char ma[maxn][maxn];
int n, m, sx, sy, len;
double da, db;
double ans;

static int dx[4] = {0, 0, 1, -1};
static int dy[4] = {1, -1, 0, 0};

#define pr(x) cout << #x << " = " << x << " $ ";
#define pn cout << endl;

double calcans(vector<pair<int, int> > s) {
    double ret = 0;
    map<pair<int, int>, int> tmp;
    for (int i = 1; i < s.size(); i++) {
        tmp[s[i]]++;
    }
    for (map<pair<int, int>, int>::iterator it = tmp.begin(); it != tmp.end(); it++) {
        pair<int, int> t;
        t = it -> first;
        double delta;
        if (ma[t.first][t.second] == 'A')
            delta = 1 - pow(1.0 - da, it -> second);
        else 
            delta = 1 - pow(1.0 - db, it -> second);
        ret += delta;
    }
    ans = max(ans, ret);
}

bool inline isvalid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void dfs(int x, int y, int step, vector<pair<int, int> > s) {
    s.push_back(make_pair(x, y));
    if (step == 0) {
        calcans(s);
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (isvalid(x + dx[i], y + dy[i])) {
            dfs(x + dx[i], y + dy[i], step - 1, s);
        }
    }
}

int main() {
    int t, kase = 0;
    scanf("%d", &t);
    while (t--) {
        vector<pair<int, int> > s;
        memset(ma, 0, sizeof(ma));
        scanf("%d %d %d %d %d\n", &n, &m, &sx, &sy, &len);
        scanf("%lf %lf\n", &da, &db);
        for (int i = 0; i < n; i++) {
            string t;
            getline(cin, t);
            for (int j = 0; j < t.size(); j++) {
                if (j % 2 == 0)
                    ma[i][j / 2] = t[j];
            }
        }
        ans = 0;
        dfs(sx, sy, len, s);
        printf("Case #%d: %.10lf\n", ++kase, ans);
    }
    return 0;
}
