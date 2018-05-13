class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* ret = new ListNode(0);
        ListNode* cur = ret;
        while (l1 || l2) {
            int t;
            if (l1 && !l2) t = l1 -> val, l1 = l1 -> next;
            else if (!l1 && l2) t = l2 -> val, l2 = l2 -> next;
            else if (l1 -> val < l2 -> val) {
                t = l1 -> val;
                l1 = l1 -> next;
            }
            else {
                t = l2 -> val;
                l2 = l2 -> next;
            }
            cur -> next = new ListNode(t);
            cur = cur -> next;
        }
        return ret -> next;
    }
};