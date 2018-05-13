class Solution {
private:
    bool hasAnswer;
    int ans;

    void dfs(TreeNode* root, int dep) {
        // if (hasAnswer) return;
        if (root == 0) return;
        if (root -> left == 0 && root -> right == 0) {
            ans = min(ans, dep);
            hasAnswer = 1;
        }
        dfs(root -> left, dep + 1);
        dfs(root -> right, dep + 1);
    }
public:
    int minDepth(TreeNode* root) {
        if (root == 0) return 0;
        hasAnswer = 0;
        ans = 1e10;
        dfs(root, 0);
        return ans;
    }
};