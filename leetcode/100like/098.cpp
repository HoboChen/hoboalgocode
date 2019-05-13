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
    bool isValidBST(TreeNode* root, TreeNode* min = NULL, TreeNode* max = NULL) {
        if (!root) {
            return true;
        }
        if (min && root -> val <= min -> val) {
            return false;
        }
        if (max && root -> val >= max -> val) {
            return false;
        }
        return isValidBST(root -> left, min, root) && isValidBST(root -> right, root, max);
    }
};

// 20ms, 20.5MB