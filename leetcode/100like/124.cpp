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
    
    inline int f(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int l = f(root -> left);
        int r = f(root -> right);
        int val = root -> val;
        int ret = max({val, l + val, r + val});
        ans = max({ans, val, l + val, r + val, l + r + val});
        return ret;
    }
    
public:
    
    Solution() {
        ans = INT_MIN;
    }
    
    int maxPathSum(TreeNode* root) {
        f(root);
        return ans;
    }
};

// 36ms, 24.7MB