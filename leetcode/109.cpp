/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
    vector<int> tmp;

    TreeNode* newNode(int val) {
        TreeNode* ret = new TreeNode(0);
        ret -> val  = val;
        return ret;
    }

    TreeNode* buildSubTree(int l, int r) { // TODO
        if (r < l) return NULL;
        if (r == l) return newNode(tmp[l]);
        const int mid = l + (r - l) / 2;
        TreeNode* ret = newNode(tmp[mid]);
        ret -> left = buildSubTree(l, mid - 1);
        ret -> right = buildSubTree(mid + 1, r);
        return ret;
    }
public:
    TreeNode* sortedListToBST(ListNode* head) {
        tmp.clear();
        while (head) {
            tmp.push_back(head -> val);
            head = head -> next;
        }
        const auto size = tmp.size() - 1; // TODO
        return buildSubTree(0, size);
    }
};