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
    int sum;
public:
    
    Solution() : sum(0) {}
    
    TreeNode* convertBST(TreeNode* root) {
        if (root != NULL) {
            convertBST(root -> right);
            sum += root -> val;
            root -> val = sum;
            convertBST(root -> left);
        }
        return root;
    }
};

// 40ms, 23.7MB