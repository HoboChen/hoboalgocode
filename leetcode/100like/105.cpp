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
    vector<int> p;
    
    TreeNode* helper(const vector<int>& in, int l, int r) {
        if (l == r) {
            return NULL;
        }
        TreeNode* root = new TreeNode(p[cnt++]);
        int i = l;
        while (in[i] != root -> val) {
            i++;
        }
        root -> left = helper(in, l, i);
        root -> right = helper(in, i + 1, r);
        return root;
    }
    
public:
    
    Solution() : cnt(0) { }
    
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        p = preorder;
        return helper(inorder, 0, inorder.size());
    }
    
};

// 24ms, 16.4MB