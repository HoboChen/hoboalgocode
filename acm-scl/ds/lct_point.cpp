#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 30000 + 10000;

struct node {
    long long val, max, inc, sum, set;
    bool rev;
    node *par, *Ch[2];
} dt[MAXN], *NIL = dt;

struct LinkcutTree {
    inline void _inc (node * x,  int inc) {
        if (x == NIL) return;
        x->inc += inc, x->val += inc, x->max += inc, x->sum += inc; // TODO sum!
    }
    inline void _set (node *x,   int set) { // TODO all
        if (x == NIL) return;
        x->set = set, x->val = set, x->max = set, x->sum = set; 
    }
    inline void clear (node *const x) {
        if (x == NIL) return ;
        if (x->inc) {
            _inc (x->Ch[0], x->inc);
            _inc (x->Ch[1], x->inc);
            x->inc = 0;
        }
        if (x->set) {
            _set (x->Ch[0], x->set);
            _set (x->Ch[0], x->set);
            x->set = 0;
        }
        if (x->rev) {
            swap (x->Ch[0], x->Ch[1]);
            x->Ch[0]->rev ^= 1;
            x->Ch[1]->rev ^= 1;
            x->rev = 0;
        }
    }
    inline void update (node * x) {
        clear (x);
        clear (x->Ch[0]), clear (x->Ch[1]);
        x->max = max (x->val, max (x->Ch[0]->max, x->Ch[1]->max) );
        x->sum = x->val + x->Ch[0]->sum + x->Ch[1]->sum;
    }
    void Rotate (node *x) {
        node *p = x->par, *g = p->par;
        clear (p),clear (x);
        int c = p->Ch[0] == x; //0左旋，1右旋
        p->Ch[c ^ 1] = x->Ch[c];
        if (x->Ch[c] != NIL) x->Ch[c]->par = p;
        x->par = g;
        if (g->Ch[0] == p) g->Ch[0] = x; else
            if (g->Ch[1] == p) g->Ch[1] = x;
        x->Ch[c] = p;
        p->par = x;
        update (p);
    }
    void Splay (node *x) {
        if(x==NIL) return ;
        while (x->par != NIL && (x->par->Ch[0] == x || x->par->Ch[1] == x) ) {
            if (x->par != NIL)
                Rotate (x);
            else {
                node *p = x->par, *g = p->par;
                if ( (g->Ch[1] == p) == (p->Ch[1] == x) )
                    Rotate (p), Rotate (x);
                else
                    Rotate (x), Rotate (x);
            }
        }
        update (x);
    }
    node *Access (node *u) {
        node *v = NIL;
        for (; u != NIL; u = u->par) {
            Splay (u);
            u->Ch[1] = v;
            update (v = u);
        }
        return v;
    }
    node *getroot (node *x) {
        for (x = Access (x); clear (x), x->Ch[0] != NIL; x = x->Ch[0]);
        return x;
    }
    inline void evert (node *x) {
        Access (x)->rev ^= 1;
        Splay (x);
    }
    inline void link (node *x, node *y) {
        evert (x);
        x->par = y;
        Access (x);
    }
    inline void cut (node *x, node *y) {
        evert (x);
        Access (y);
        Splay (y);
        y->Ch[0]->par = NIL;
        y->Ch[0] = NIL;
        update (y);
    }
    inline long long querymax (node *x, node *y) {
        evert (x);
        Access (y), Splay (y);
        return y->max;
    }
    inline long long querysum (node *x, node *y) {
        evert (x);
        Access (y), Splay (y);
        return y->sum;
    }
    inline void pathadd (node *x, node *y, int w) {
        evert (x);
        Access (y), Splay (y);
        _inc (y, w);
    }
    inline void pathset (node *x, node *y, int w) {
        evert (x);
        Access (y), Splay(y);
        _set (y, w);
    }
    inline void pointset (node *x, int w) {
        Splay(x);
        x->val = w;
        update(x);
    }
    inline void pointadd (node *x, int w) {
        Splay(x);
        x->val += w;
        update(x);
    }
} LCT;
int n, m;

int main() {
    while (scanf ("%d", &n) != EOF) {
        for (int i = 0; i <= n; i++) {
            dt[i].sum = dt[i].val = dt[i].inc = 0;
            dt[i].max = -0x3e3e3e3e;
            dt[i].par = dt[i].Ch[0] = dt[i].Ch[1] = NIL;
            dt[i].rev = 0;
        }
        for (int i = 1, x, y; i < n; ++i) {
            scanf ("%d %d", &x, &y);
            LCT.link (dt + x, dt + y);
        }
        for (int i = 1, x; i <= n; ++i) {
            scanf ("%d", &x);
            node *tem = dt + i;
            LCT.Splay (tem);
            tem->sum = tem->val = tem->max = x;
            LCT.update (tem);
        }
        scanf ("%d", &m);
        char op[10];
        for (int i = 0, x, y; i < m; ++i) {
            scanf ("%s %d %d\n", op, &x, &y);
            switch (op[1]) {
                case 'M':
                    printf("%lld\n", LCT.querymax (dt + x, dt + y)); break;
                case 'S':
                    printf("%lld\n", LCT.querysum (dt + x, dt + y)); break;
                case 'H':
                    LCT.pointset (dt + x, y); break;
            }
        }
        /* printf("\n"); */
    }
    return 0;
}

