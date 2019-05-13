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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        queue<pair<TreeNode*, int>> q;
        q.push(make_pair(root, 1));
        while (!q.empty()) {
            const auto p = q.front();
            q.pop();
            if (!p.first) {
                continue;
            }
            if (ret.size() < p.second) {
                ret.push_back(vector<int>{p.first -> val});
            } else {
                ret[p.second - 1].push_back(p.first -> val);
            }
            q.push(make_pair(p.first -> left, p.second + 1));
            q.push(make_pair(p.first -> right, p.second + 1));
        }
        return ret;
    }
};

// 20ms, 13.8MB