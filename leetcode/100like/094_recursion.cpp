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
    vector<int> mAnswer;
    
    void helper(TreeNode* root) {
        if (!root) {
            return;
        }
        helper(root -> left);
        mAnswer.push_back(root -> val);
        helper(root -> right);
    }
    
public:
    vector<int> inorderTraversal(TreeNode* root) {
        helper(root);
        return mAnswer;
    }
};

// 4ms, 9.4MB