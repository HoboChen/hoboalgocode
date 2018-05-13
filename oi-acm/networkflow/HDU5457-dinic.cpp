
#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

struct Edge {
    int u, v, cap;
    Edge() {}
    Edge(int u, int v, int cap): u(u), v(v), cap(cap) {}
};

int R, S, T;

const int maxe = 15000; 
const int maxp = 5000;
const int inf = 0x3f3f3f3f;

Edge es[maxe];
vector<int> tab[maxp];
int dis[maxp], current[maxp];

void init() {
    R = 0;
    memset(es, 0, sizeof(es));
    for (int i = 0; i < maxp; i++) 
        tab[i].clear();
}

void addedge(int u, int v, int cap, int rw = 0) {
    tab[u].push_back(R);
    es[R++] = Edge(u, v, cap);
    tab[v].push_back(R);
    es[R++] = Edge(v, u, rw);
}

int BFS() {
    queue<int> q;
    q.push(S);
    memset(dis, 0x3f, sizeof(dis));
    dis[S] = 0;
    while (!q.empty()) {
        int h = q.front();
        q.pop();
        for (int i = 0; i < tab[h].size(); i++) {
            Edge &e = es[tab[h][i]];
            if (e.cap > 0 && dis[e.v] == inf) {
                dis[e.v] = dis[h] + 1;
                q.push(e.v);
            }
        }
    }
    return dis[T] < inf;
}

int dinic(int x, int maxflow) {
    if (x == T || maxflow == 0)
        return maxflow;
    for (int i = current[x]; i < tab[x].size(); i++) {
        current[x] = i;
        Edge &e = es[tab[x][i]];
        if (dis[e.v] == dis[x] + 1 && e.cap > 0) {
            int flow = dinic(e.v, min(maxflow, e.cap));
            if (flow) {
                e.cap -= flow;
                es[tab[x][i] ^ 1].cap += flow;
                return flow;
            }
        }
    }
    return 0;
}

int dinic() {
    int ans = 0;
    while (BFS()) {
        int flow;
        memset(current, 0, sizeof(current));
        while (flow = dinic(S, 0x3f3f3f3f))
            ans += flow;
    }
    return ans;
}

const int maxn = 1000;
const double eps = 1e-10;

const int childsize = 2;

int sumnu;

struct node {
    int val, nu;
    int sum;
    int iq[childsize];
    
    node * c[childsize];
    
    node() { }

    static node * newnode(int x) {
        node *tmp = new node;
        tmp -> val = x;
        memset(tmp -> iq, inf, sizeof(int) * childsize);
        tmp -> nu = ++sumnu;
        memset(tmp -> c, 0, sizeof(tmp) * childsize);
        return tmp;
    }
};

node *rootor, *rootre;

map<int, int> or2re;

inline node* build() {
    node * root = node::newnode(-1); 
    root -> sum = 0; 
    return root; 
}

int add(int x, node *root, bool orderd) {
    int *p = (int *)calloc(8, sizeof(int));
    for (int i = 0; i < 8; i++)  {
        p[i] = x % 2;
        x /= 2;
    }
    if (orderd) reverse(p, p + 8);
    node *pos = root;
    int cnt;
    for (int i = 0; i < 8; i++) {
        if (!(pos -> c[p[i]])) {
             pos -> c[p[i]] = node::newnode(p[i]);
             pos -> c[p[i]] -> sum = pos -> sum * 2;
             pos -> c[p[i]] -> sum += p[i];
             pos = pos -> c[p[i]];
             cnt  = pos -> nu;
             continue;
        }
        pos = pos -> c[p[i]];
    }
    delete p;
    return cnt;
}

void add(int x) {
    int a = add(x, rootor, 1);
    int b = add(x, rootre, 0);
    or2re[a] = b;
}

inline bool isleaf(node * x) {
    for (int i = 0; i < childsize; i++)
        if (x -> c[i]) 
            return 0;
    return 1;
}

void dfs(node * root, bool ispre) {
    for (int i = 0; i < childsize; i++)
        if (root -> c[i]) {
            if (ispre) addedge(root -> nu, root -> c[i] -> nu, root -> iq[i]);
            else addedge(root -> c[i] -> nu, root -> nu, root -> iq[i]);
            dfs(root -> c[i], ispre);
        }
    delete root;
}

void updatecapacity(const char * s, int len, node * root, int d) {
    node *pos = root;
    for (int i = 0; i < len - 1; i++) {
        if (!(pos -> c[s[i] - '0']))
            return;
        pos = pos -> c[s[i] - '0'];
    }
    if (!(pos -> c[s[len - 1] - '0']))
        return;
    pos -> iq[s[len - 1] - '0'] = min(pos -> iq[s[len - 1] - '0'], d);
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        init();
        sumnu = 0;
        or2re.clear();
        rootor = build();
        rootre = build();
        int n, m;
        scanf("%d%d", &n, &m);
        for (int j = 0; j < n; j++) {
            int t;
            scanf("%d", &t);
            add(t);
        }
        char t[100];
        gets(t);
        for (int j = 0; j < m; j++) {
            char buf[100];
            memset(buf, 0, sizeof(buf));
            char op;
            char s[8];
            int cost;
            gets(buf);
            sscanf(buf, "%c %s %d", &op, s, &cost);
            if (op == 'P')
                updatecapacity(s, strlen(s), rootor, cost);
            if (op == 'S') {
                reverse(s, s + strlen(s));
                updatecapacity(s, strlen(s), rootre, cost);
            }
           
        }
        S = rootor -> nu;
        T = rootre -> nu;
        dfs(rootor, 1);
        dfs(rootre, 0);
        for (map<int, int>::iterator j = or2re.begin(); j != or2re.end(); j++)
            addedge(j -> first, j -> second, inf);
        int ans = dinic(); 
        if (ans >= inf) ans = -1;
        printf("Case #%d: %d\n", i, ans);
    }
    return 0;
}
