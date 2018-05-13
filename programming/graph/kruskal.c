#include <stdio.h>
#include <stdlib.h>

#define max_v 1000
#define max_e 10000

typedef struct edge_struct {
    int u, v, w;
}edge;

int p[max_v];

int find(int x) {
	return p[x] == x ? x : (p[x] = find(p[x]));
}

void merge(int i, int j) {
	int x = find(i);
	int y = find(j);
	if (x > y) p[y] = x;
	else p[x] = y;
}

edge edges[max_e];
int cnt;

void add_edge(int u, int v, int w) {
    edges[cnt].u = u;
    edges[cnt].v = v;
    edges[cnt].w = w;
    cnt++;
}

int edge_cnt(edge* x, edge* y) {
    if (x -> w == y -> w) {
        return 0;
    } 
    if (x -> w > y -> w) {
        return 1;
    }
    return -1;
}

int kruskal() {
    int ret = 0;
    qsort(edges, cnt, sizeof(edge), &edge_cnt);
    for (int i = 0; i < cnt; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find(u) == find(v)) {
            continue;
        }
        ret += edges[i].w;
        merge(u, v);
    }
    return ret;
}

int main() {
    for (int i = 0; i < max_v; i++) {
        p[i] = i;
    }
    add_edge(0, 2, 5);
    add_edge(0, 3, 5);
    add_edge(3, 4, 5);
    add_edge(0, 1, 1);
    add_edge(1, 2, 1);
    add_edge(2, 3, 1);
    add_edge(4, 1, 1);
    printf("%d", kruskal());
    return 0;
}