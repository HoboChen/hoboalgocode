#include <bits/stdc++.h>

using namespace std;

const int maxn = 100000;

#define pr(x) cout << #x << " = " << x << " $ ";
#define pn cout << endl;

int n, cnt, ff;
int din[maxn], L[maxn];
vector<int> G[maxn];
map<string, int> dict;
map<string, set<string>> graph;

void init() {
    cnt = 0;
    memset(din, 0, sizeof(din));
    for (int i = 0; i < maxn; i++)
        G[i].clear();
    dict.clear();
    graph.clear();
}

bool toposort(int n, vector<int> g[]) {
    int * du = new int[maxn];
    memset(du, 0, sizeof(int) * maxn);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < g[i].size(); j++)
            du[g[i][j]]++;
    int tot = 0;
    queue<int> Q;
    for (int i = 0; i < n; i++)
        if (!du[i]) Q.push(i);
    while (!Q.empty()) {
        int x = Q.front(); Q.pop();
        tot++;
        for (int j = 0; j < g[x].size(); j++) {
            int t = g[x][j];
            du[t]--;
            if (!du[t]) Q.push(t);
        }
    }
    delete du;
    return tot == n;
}

void add_edge(string t) {
    int lpos = 0, rpos = 0;
    while (t[lpos] != '=') lpos++;
    string ss = t.substr(0, lpos);
    while (t[lpos] != '(') lpos++;
    rpos = lpos;
    while (t[rpos] != ')') rpos++;
    vector<int> pp;
    pp.push_back(lpos);
    for (int i = lpos + 1; i < t.size() - 1; i++) { if (t[i] == ',') pp.push_back(i); }
    pp.push_back(t.size() - 1);
    graph[ss].insert("###");
    graph["###"].insert("###");
    for (int i = 0; i < pp.size() - 1; i++) {
        int l = pp[i], r = pp[i + 1];
        string x = t.substr(l + 1, r - l - 1);
        if (x == "") continue;
        if (x == ss) { ff = 0; return; }
        graph[ss].insert(x);
    }
}

void gen_graph() {
    for (auto i = graph.begin(); i != graph.end(); i++) {
        if (dict.find(i -> first) == dict.end()) dict[i -> first] = cnt++;
        int S = dict[i -> first];
        for (auto j = i -> second.begin(); j != i -> second.end(); j++) {
            if (graph.find(*j) == graph.end()) { ff = 0; return; }
            if (dict.find(*j) == dict.end()) dict[*j] = cnt++;
            if (*j != "###") G[S].push_back(dict[*j]);
        }
    }
}

int main() {
    int t, kase = 0;
    scanf("%d\n", &t);
    while (t--) {
        ff = 1;
        init();
        scanf("%d\n", &n);
        for (int i = 0; i < n; i++) {
            string tmp;
            getline(cin, tmp);
            add_edge(tmp);
        }
        gen_graph();
        printf("Case #%d: ", ++kase);
        if (toposort(cnt, G) * ff) printf("GOOD\n");
        else printf("BAD\n");
    }
    return 0;
}
