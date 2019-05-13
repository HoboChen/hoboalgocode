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
    
    map<pair<TreeNode*, bool>, int> dp;

    inline int dfs(TreeNode* root, bool rob) {
        if (!root) {
            return 0;
        }
        if (dp.find(make_pair(root, rob)) != dp.end()) {
            return dp[make_pair(root, rob)];
        }
        if (rob) {
            int l = dfs(root -> left, 0);
            int r = dfs(root -> right, 0);
            return dp[make_pair(root, rob)] = l + r + root -> val;
        }
        int l = max(dfs(root -> left, 1), dfs(root -> left, 0));
        int r = max(dfs(root -> right, 1), dfs(root -> right, 0));
        return dp[make_pair(root, rob)] = l + r;
    }

public:
    int rob(TreeNode* root) {
        return max(dfs(root, 1), dfs(root, 0));
    }
};

// 44ms, 27.4MB