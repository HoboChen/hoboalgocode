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
    
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = NULL;
        ListNode* tail = NULL;
        int extra = 0;
        while (l1 || l2 || extra) {
            extra += l1 ? l1 -> val : 0;
            extra += l2 ? l2 -> val : 0;
            if (!tail) {
                head = tail = new ListNode(extra % 10);
            } else {
                tail -> next = new ListNode(extra % 10);
                tail = tail -> next;
            }
            extra /= 10;
            l1 = l1 ? l1 -> next : l1;
            l2 = l2 ? l2 -> next : l2;
        }
        return head;
    }
};

// 40ms, 19.1MB