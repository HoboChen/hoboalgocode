#include <bits/stdc++.h>

using namespace std;

struct trienode {
    static const int childsize = 26;
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

trienode * root;

inline node* build() {
    node * root = node::newnode(-1); 
    root -> sum = 0; 
    return root; 
}

int main() {

    return 0;
}