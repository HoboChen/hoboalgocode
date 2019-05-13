#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define max_son_number_uint 2

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct treenode_struct{
    int val;
    struct treenode_struct* left;
    struct treenode_struct* right;
    struct treenode_struct* father;
    unsigned int height;
    unsigned int cnt;
}treenode;

static treenode* treenode_newnode(int val, treenode* father) {
    treenode* ret = malloc(sizeof(treenode));
    memset(ret, 0, sizeof(treenode));
    ret -> val = val;
    ret -> father = father;
    ret -> cnt = 1;
    return ret;
}

void avl_update_height(treenode* nd) {
    int height_left = nd -> left ? nd -> left -> height : -1;
    int height_right = nd -> right ? nd -> right -> height : -1;
    nd -> height = max(height_left, height_right) + 1;
}

int avl_is_balanced(treenode* nd) {
    int height_left = nd -> left ? nd -> left -> height : -1;
    int height_right = nd -> right ? nd -> right -> height : -1;
    return abs(height_left - height_right) < 2;
}

treenode* avl_left_left(treenode* root) {
    treenode* new_root = root -> left;

    root -> left = new_root -> right;
    new_root -> right = root;
    
    avl_update_height(root);
    avl_update_height(new_root);

    return new_root;
}

treenode* avl_right_right(treenode* root) {
    treenode* new_root = root -> right;

    root -> right = new_root -> left;
    new_root -> left = root;

    avl_update_height(root);
    avl_update_height(new_root);

    return new_root;
}

treenode* avl_left_right(treenode* root) {
    root -> left = avl_right_right(root -> left);
    return avl_left_left(root);
}

treenode* avl_right_left(treenode* root) {
    root -> right = avl_left_left(root -> right);
    return avl_right_right(root);
}

treenode* avl_insert(treenode* root, int val) {
    if (root == NULL) {
        root = treenode_newnode(val, NULL);
        return root;
    }  
    else if (val < root -> val) {
        root -> left = avl_insert(root -> left, val);
        if (!avl_is_balanced(root)) {
            if (val < root -> left -> val) {
                root = avl_left_left(root);
            }
            else {
                root = avl_left_right(root);
            }
        }
    }
    else if (val > root -> val) {
        root -> right = avl_insert(root -> right, val);
        if (!avl_is_balanced(root)) {
            if (val > root -> right -> val) {
                root = avl_right_right(root);
            }
            else {
                root = avl_right_left(root);
            }
        }
    }
    else {
        root -> cnt += 1;
    }
    avl_update_height(root);
    return root;
}

void tree_print(treenode* root) {
    if (root == NULL) {
        return;
    }
    printf("value: %d, address: %x, count:%d\n", root -> val, root, root -> cnt);
    if (root -> left) {
        printf("\tvalue: %d, address: %lx\n", root -> left -> val, root -> left);
    }
    if (root -> right) {
        printf("\tvalue: %d, address: %lx\n", root -> right -> val, root -> right);
    }
    tree_print(root -> left);
    tree_print(root -> right);
}

int is_avl(treenode* root, int* ans) { // the return val is the depth
    if (root == NULL) {
        return 0;
    }
    int height_left = is_avl(root -> left, ans);
    int height_right = is_avl(root -> right, ans);
    if (abs(height_left - height_right) >= 2) {
        *ans = 0;
    }
    return max(height_left, height_right) + 1;
}

int get_height(treenode* root) {
    if (root == NULL) {
        return 0;
    }
    int height_left = get_height(root -> left);
    int height_right = get_height(root -> right);
    int height = max(height_left, height_right) + 1;
    printf("value: %d, address: %x, height:%d\n", root -> val, root, height);
    return height;
}

void get_depth(treenode* root, int depth) {
    if (root == NULL) {
        return;
    }
    printf("value: %d, address: %x, depth:%d\n", root -> val, root, depth);
    get_depth(root -> left, depth + 1);
    get_depth(root -> right, depth + 1);
}

typedef struct queue_s {
    treenode* val[1000];
    int head, tail;
}queue;

queue q;

void push(treenode* s) {
    q.val[q.tail++] = s;
}

treenode* pop() {
    return q.val[q.head++];
}

int is_empty() {
    return q.head >= q.tail;
}

void print_levelorder(treenode* root) {
    push(root);
    while (!is_empty()) {
        treenode* f = pop();
        if (f) {
            printf("%d ", f -> val);
        }
        if (f -> left) {
            push(f -> left);
        }
        if (f -> right) {
            push(f -> right);
        }
    }
}

void test_1() {
    treenode* root = 0;
    for (int i = 1; i <= 10; i++) {
        root = avl_insert(root, i);
    }
    // tree_print(root); 
    // get_height(root);
    // get_depth(root, 1);
    print_levelorder(root);
}

int main() {
    test_1();
    return 0;
}