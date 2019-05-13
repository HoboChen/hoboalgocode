#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <deque>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <stack>
#include <deque>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <climits>


using namespace std;

#ifdef ONLINE_JUDGE
#define fio 0
#else
#define fio 1
#endif

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;
inline void px(string s) { cout << s << ends; }

const int maxn = 200000 + 10000;
const int inf = 0x3e3e3e3e;
const long long llinf = (long long)0x3e3e3e3e * 0x3e3e3e3e;

const double eps = 1e-10;

#define nodenu int

void clear();
void splay(nodenu, int); // node and node
void insert(int); // insert a value
void remove(int); // remove a value
void rotate(int, short); // rotate a splaynode
int splayfind(int); // find the value, return node
void splayfind(int, int);

struct splaynode {
    int ch[2], v, pa, sz; // left, right, val, parent, size
    splaynode() { }
    splaynode(int x, int p) { ch[0] = ch[1] = 0; sz = 1; v = x; pa = p; }
};

splaynode node[maxn];
int root, tot;

void buildroot(int x) { node[tot++] = splaynode(x, 0); root = 1;}
int addnode(int x, int p) {node[tot++] = splaynode(x, p); return tot - 1; }

void clear() {
    root = 0;
    tot = 1;
    memset(node, 0, sizeof(0));
    insert(INT_MIN);
    insert(INT_MAX);
}

void updatesize(int p) {
    if (p == 0) return;
    node[p].sz = node[node[p].ch[0]].sz + node[node[p].ch[1]].sz + 1;
}

void insert(int x) {
    if (!root) { buildroot(x); return ; }
    int cur = root;
    while (1) {
        int dir = x > node[cur].v;
        if (!node[cur].ch[dir]) {
            node[cur].ch[dir] = addnode(x, cur);
            updatesize(cur);
            splay(node[cur].ch[dir], 0);
            return;
        }
        else cur = node[cur].ch[dir];
    }
}

void remove(int val) {
    int k = splayfind(val);
    splayfind(k - 1, 0);
    splayfind(k + 1, root);
    node[node[root].ch[1]].ch[0] = 0;
    updatesize(node[root].ch[1]);
    updatesize(root);
}

void rotate(int x, short dir) {
    int p = node[x].pa;
    node[p].ch[dir ^ 1] = node[x].ch[dir];
    node[node[p].ch[dir ^ 1]].pa = p;
    node[x].ch[dir] = p;
    node[x].pa = node[p].pa;
    if (node[node[p].pa].ch[0] == p)
        node[node[p].pa].ch[0] = x;
    else
        node[node[p].pa].ch[1] = x;
    node[p].pa = x;
    updatesize(p);
    updatesize(x);
    if (root == p) root = x;
}

void splay(int x, int y) {
    while (node[x].pa != y) {
        if (node[node[x].pa].pa == y) {
            if (node[node[x].pa].ch[0] == x) rotate(x, 1);
            else rotate(x, 0);
        }
        else if (node[node[node[x].pa].pa].ch[0] == node[x].pa) {
            if (node[node[x].pa].ch[0] == x) rotate(node[x].pa, 1), rotate(x, 1);
            else rotate(x, 0), rotate(x, 1);
        }
        else {
            if (node[node[x].pa].ch[1] == x) rotate(node[x].pa, 0), rotate(x, 0);
            else rotate(x, 1), rotate(x, 0);
        }
        updatesize(x);
    }
}

inline int getkth(int k) { splayfind(k + 1, 0); return node[root].v; }

void splayfind(int k, int y) {
    int cur = root;
    while (k != node[node[cur].ch[0]].sz + 1) {
        if (k <= node[node[cur].ch[0]].sz)
            cur = node[cur].ch[0];
        else {
            k -= node[node[cur].ch[0]].sz + 1;
            cur = node[cur].ch[1];
        }
    }
    splay(cur, y);
}

int splayfind(int value) {
    int cur = root, cnt = 0;
    while (1) {
        if (node[cur].v == value)
            return cnt + node[cur].sz - node[node[cur].ch[1]].sz;
        else if (node[cur].v > value)
            cur = node[cur].ch[0];
        else {
            cnt += node[cur].sz - node[node[cur].ch[1]].sz;
            cur = node[cur].ch[1];
        }
    }
}

void printpreorder(int);

void splayprint() {
    printf("Splay Tree: \n");
    printpreorder(root);
    printf("\n");
}

void printpreorder(int p) {
    if (p == 0) return;
    printf("%d: %d %d %d\n", node[p].v, node[node[p].ch[0]].v, node[node[p].ch[1]].v, node[p].sz);
    printpreorder(node[p].ch[0]);
    printpreorder(node[p].ch[1]);
}

const int maxm = 50000 + 10000;
int prt[maxn], ans[maxm];

struct seg { 
    int l, r, k, idx; 
    bool operator < (const seg & x) const {
        return r < x.r;
    }
};
seg ss[maxm];

int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        clear();
        for (int i = 1; i <= n; i++) 
            scanf("%d", &prt[i]);
        for (int i = 1; i <= m; i++) {
            scanf("%d%d%d", &ss[i].l, &ss[i].r, &ss[i].k);
            ss[i].idx = i;
        }
        sort(ss + 1, ss + m + 1);
        int prel = 1, prer = 0;
        for (int i = 1; i <= m; i++) {
            for (int j = prel; j < ss[i].l && j <= prer; j++) 
                remove(prt[j]);
            for (int j = max(ss[i].l, prer + 1); j <= ss[i].r; j++) 
                insert(prt[j]);
            prel = ss[i].l;
            prer = ss[i].r;
            ans[ss[i].idx] = getkth(ss[i].k); //TODO
        }
        for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    }
    return 0;
}

