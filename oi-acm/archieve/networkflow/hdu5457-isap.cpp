
#include <bits/stdc++.h>

using namespace std;

#define pr(x) cout << #x << " = " << x << " # ";
#define pn cout << endl;

const int MAXN = 5000;
const int MAXM = 15000;
const int INF = 0x3f3f3f3f;

struct Edge {
	int to, next, cap, flow;
	void c(int t, int n, int c, int f) {
		to = t;
		next = n;
		cap = c;
		flow = f;
	}
}edge[MAXM];

int tol, head[MAXN], gap[MAXN], dep[MAXN], cur[MAXN];

void init() {
	tol = 0;
	memset(head, -1, sizeof(head));
}

int summ;

void addedge(int u, int v, int w, int rw = 0) {
    edge[tol].c(v, head[u], w, 0);
	head[u] = tol++;
	edge[tol].c(u, head[v], rw, 0);
	head[v] = tol++;
    summ++;
}

int Q[MAXN];

void BFS(int start, int end) {
	memset(dep, -1, sizeof(dep));
	memset(gap, 0, sizeof(gap));
	gap[0] = 1;
	int front = 0, rear = 0;
	dep[end] = 0;
	Q[rear++] = end;
	while(front != rear) {
		int u = Q[front++];
		for(int i = head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].to;
			if (dep[v] != -1) continue;
			Q[rear++] = v;
			dep[v] = dep[u] + 1;
			gap[dep[v]]++;
		}
	}
}

int S[MAXN];

int isap(int start, int end, int N) {
	BFS(start, end);
	memcpy(cur, head, sizeof(head));
	int top = 0, u = start, ans = 0;
	while (dep[start] < N) {
		if (u == end) {
			int Min = INF, inser;
			for (int i = 0;i < top;i++)
				if(Min > edge[S[i]].cap - edge[S[i]].flow) {
					Min = edge[S[i]].cap - edge[S[i]].flow;
					inser = i;
				}
			for (int i = 0;i < top;i++) {
				edge[S[i]].flow += Min;
				edge[S[i]^1].flow -= Min;
			}
			ans += Min;
			top = inser;
			u = edge[S[top]^1].to;
			continue;
		}
		bool flag = false;
		int v;
		for (int i = cur[u]; i != -1; i = edge[i].next) {
			v = edge[i].to;
			if (edge[i].cap - edge[i].flow && dep[v] + 1 == dep[u]) {
				flag = true;
				cur[u] = i;
				break;
			}
		}
		if (flag) {
			S[top++] = cur[u];
			u = v;
			continue;
		}
		int Min = N;
		for(int i = head[u]; i != -1; i = edge[i].next)
			if(edge[i].cap - edge[i].flow && dep[edge[i].to] < Min) {
				Min = dep[edge[i].to];
				cur[u] = i;
			}
		gap[dep[u]]--;
		if (!gap[dep[u]]) return ans;
		dep[u] = Min + 1;
		gap[dep[u]]++;
		if(u != start) u = edge[S[--top]^1].to;
	}
	return ans;
}

const int maxn = 1000;
const double eps = 1e-10;
const int inf = 0x3e3e3e3e;

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
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        init();
        sumnu = 0;
        summ = 0;
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
        int S = rootor -> nu, T = rootre -> nu;
        dfs(rootor, 1);
        dfs(rootre, 0);
        for (map<int, int>::iterator j = or2re.begin(); j != or2re.end(); j++)
            addedge(j -> first, j -> second, inf);
        int ans = isap(S, T, sumnu);
        if (ans >= inf) ans = -1;
        printf("Case #%d: %d\n", i, ans);
    }
    return 0;
 }
