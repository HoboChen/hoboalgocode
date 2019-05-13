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
    
    ListNode* reverseList(ListNode* head) {
        if (!head || !head -> next) {
            return head;
        }
        ListNode* cur = head -> next;
        head -> next = NULL;
        while (cur) {
            ListNode* t = cur -> next;
            cur -> next = head;
            head = cur;
            cur = t;
        }
        return head;
    }
    
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !(head -> next)) {
            return true;
        }
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast -> next && fast -> next -> next) {
            fast = fast -> next -> next;
            slow = slow -> next;
        }
        // slow in the middle
        slow -> next = reverseList(slow -> next);
        ListNode* cur = slow -> next;
        while (cur) {
            if (head -> val != cur -> val) {
                return false;
            }
            head = head -> next;
            cur = cur -> next;
        }
        return true;
    }
};

// 24ms, 12.7MB