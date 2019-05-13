class Solution {
public:
    int maxDepth(TreeNode* root, int depth = 0) {
        if (!root) {
            return depth;
        }
        return max(maxDepth(root -> left, depth + 1), maxDepth(root -> right, depth + 1));
    }
};

// 16ms, 19.4MB