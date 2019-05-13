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
    int ans;
    
    int helper(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int left = helper(root -> left);
        int right = helper(root -> right);
        ans = max({ans, left + right + 1});
        return max({left, right}) + 1;
    }
    
public:
    int diameterOfBinaryTree(TreeNode* root) {
        ans = 1;
        helper(root);
        return ans - 1;
    }
};

// 24ms, 19.9MB