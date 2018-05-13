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

void tree_insert(treenode* root, int val) {
    if (root -> son[val > root -> val]) {
        tree_insert(root -> son[val > root -> val], val);
        return;
    }
    root -> son[val > root -> val] = treenode_newnode(val, root);
}

void tree_delete(treenode* root, treenode* to_delete) {
    // todo
}

// must be an binary tree
void tree_print_inorder(treenode* root) {
    if (root == NULL) {
        return;
    }
    tree_print_inorder(root -> son[0]);
    printf("%d ", root -> val);
    tree_print_inorder(root -> son[1]);
}

void test_1() {
    int v[] = {17, 2, 5, 7, 3, 4, 1};
    treenode* root = treenode_newnode(v[0], NULL);
    for (int i = 1; i < 7; i++) {
        tree_insert(root, v[i]);
    }
    tree_print_inorder(root);
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

void test_2() {
    printf("test_2:\n");
    int v[] = {17, 2, 5, 7, 3, 4, 1};
    treenode* root = treenode_newnode(v[0], NULL);
    for (int i = 1; i < 7; i++) {
        tree_insert(root, v[i]);
    }
    tree_print(root);
    printf("end_of_test_2\n");
}

int main() {
    test_2();
    return 0;
}