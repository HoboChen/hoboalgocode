/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void flatten(TreeNode* root) {
        if (!root) {
            return;
        }
        flatten(root -> right);
        flatten(root -> left);
        TreeNode* right = root -> right;
        root -> right = root -> left;
        root -> left = NULL;
        while (root -> right) {
            root = root -> right;
        }
        root -> right = right;
    }
};

// 8ms, 9.7MB