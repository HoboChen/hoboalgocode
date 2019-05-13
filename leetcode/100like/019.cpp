/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* tmp = new ListNode(0);
        tmp -> next = head;
        ListNode* a = tmp;
        ListNode* kth = tmp;
        for (int i = 0; i < n + 1; i++) {
            a = a -> next;
        }
        while (a) {
            a = a -> next;
            kth = kth -> next;
        }
        kth -> next = kth -> next -> next;
        return tmp -> next;
    }
};

// 4ms, 8.5MB