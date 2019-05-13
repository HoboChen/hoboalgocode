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
private:
    TreeNode* prev;
public:
    void flatten(TreeNode* root) {
        if (!root) {
            return;
        }
        flatten(root -> right);
        flatten(root -> left);
        root -> right = prev;
        root -> left = NULL;
        prev = root;
    }
};

// 12ms, 9.5MB