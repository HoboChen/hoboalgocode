class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2, TreeNode* root = NULL) {
        if (!t1 && !t2) {
            return root;
        }
        int val1 = t1 ? t1 -> val : 0;
        int val2 = t2 ? t2 -> val : 0;
        root = new TreeNode(val1 + val2);
        root -> left = mergeTrees(t1 ? t1 -> left : NULL, t2 ? t2 -> left : NULL);
        root -> right = mergeTrees(t1 ? t1 -> right : NULL, t2 ? t2 -> right : NULL);
        return root;
    }
};

// 56ms, 23.7MB