#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max_son_number_uint 2

typedef struct treenode_struct{
    int val;
    struct treenode_struct* son[max_son_number_uint];
    struct treenode_struct* father;
}treenode;

static treenode* treenode_newnode(int val, treenode* father) {
    treenode* ret = calloc(sizeof(treenode), 1);
    ret -> val = val;
    ret -> father = father;
    return ret;
}

void tree_print(treenode* root) {
    printf("value: %d, address: %x\n",root -> val, root);
    for (int i = 0; i < max_son_number_uint; i++) {
        if (root -> son[i]) {
            printf("\tvalue: %d, address: %lx\n", root -> son[i] -> val, root -> son[i]);
        }
    }
    for (int i = 0; i < max_son_number_uint; i++) {
        if (root -> son[i]) {
            tree_print(root -> son[i]);
        }
    }
}

int main() {

    return 0;
}