/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
private:
    
    inline int length(ListNode* head) {
        int ret = 0;
        while (head) {
            ret++;
            head = head -> next;
        }
        return ret;
    }
    
public:
    ListNode* getIntersectionNode(ListNode *headA, ListNode *headB) {
        auto lenA = length(headA);
        auto lenB = length(headB);
        if (lenA > lenB) {
            for (int i = 0; i < lenA - lenB; i++) {
                headA = headA -> next;
            }
        } else {
            for (int i = 0; i < lenB - lenA; i++) {
                headB = headB -> next;
            }
        }
        while (headA != headB) {
            headA = headA -> next;
            headB = headB -> next;
        }
        return headA;
    }
};

// 52ms, 16.7MB