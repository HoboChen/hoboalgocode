class Solution {
private:
    inline int listLen(ListNode* head) {
        int ret = 0;
        ListNode* cur = head;
        while (cur) {
            ret++;
            cur = cur -> next;
        }
        return ret;
    }
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int p = listLen(head) + 1 - n;
        if (p == 1) return head -> next;
        ListNode* remove = head;
        for (int i = 0; i < p - 2; i++) remove = remove -> next;
        remove -> next = remove -> next -> next;
        return head;
    }
};