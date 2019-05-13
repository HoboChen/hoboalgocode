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
    
    inline bool hasCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast && fast -> next) {
            fast = fast -> next -> next;
            slow = slow -> next;
            if (fast == slow) {
                return true;
            }
        }
        return false;
    }
    
};

// 20ms, 9.8MB