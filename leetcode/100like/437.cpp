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
    int cnt;
    
public:
    
    Solution() {
        cnt = 0;
    }
    
    inline void f(TreeNode* root, int sum, bool isBegin) {
        if (!root) {
            return;
        }
        if (sum == root -> val) {
            cnt++;
        }
        f(root -> left, sum - root -> val, true);
        f(root -> right, sum - root -> val, true);
        if (!isBegin) {
            f(root -> left, sum, false);
            f(root -> right, sum, false);
        }
    }
    
    int pathSum(TreeNode* root, int sum) {
        f(root, sum, false);
        return cnt;
    }
};

// 28ms, 14.1MB