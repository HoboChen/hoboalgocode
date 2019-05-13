#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define number_of_sons 2

typedef struct treenode_struct{
    int val;
    struct treenode_struct* son[number_of_sons];
    struct treenode_struct* father;
}treenode;

treenode* treenode_newnode(int val, treenode* father) {
    treenode* ret = calloc(1, sizeof(treenode));
    ret -> val = val;
    ret -> father = father;
    return ret;
}

void tree_print(treenode* root) {
    printf("value: %d, address: %lx\n", root -> val, (long unsigned)root);
    for (int i = 0; i < number_of_sons; i++) {
        if (root -> son[i]) {
            printf("\tson, value: %d, address: %lx\n", root -> son[i] -> val, (long unsigned)root -> son[i]);
        }
    }
    for (int i = 0; i < number_of_sons; i++) {
        if (root -> son[i]) {
            tree_print(root -> son[i]);
        }
    }
}

int main() {

    return 0;
}