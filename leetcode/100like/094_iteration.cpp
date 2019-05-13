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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        stack<TreeNode*> s;
        TreeNode* cur = root;
        while (cur || !s.empty()) {
            while (cur) {
                s.push(cur);
                cur = cur -> left;
            }
            cur = s.top();
            s.pop();
            ret.push_back(cur -> val);
            cur = cur -> right;
        }
        return ret;
    }
};

// 4ms, 9MB