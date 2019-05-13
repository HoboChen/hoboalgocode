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
    bool isMirror(TreeNode* left, TreeNode* right) {
        if (left == NULL && right == NULL) {
            return true;
        }
        if (left == NULL || right == NULL) {
            return false;
        }
        return left -> val == right -> val && 
            isMirror(left -> left, right -> right) && 
            isMirror(left -> right, right -> left);
    }
    
public:
    bool isSymmetric(TreeNode* root) {
        return isMirror(root, root);

    }
};

// 8ms, 14.8MB