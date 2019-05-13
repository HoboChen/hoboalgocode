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
    
    inline bool hasLeft(const vector<ListNode*>& lists) {
        for (const auto& head : lists) {
            if (head) {
                return true;
            }
        }
        return false;
    }
    
public:
    
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* head = NULL;
        ListNode* current = NULL;
        priority_queue<int, vector<int>, greater<int>> q;
        bool f = hasLeft(lists);
        while (f || !q.empty()) {
            if (f) {
                bool left = false;
                for (auto& head : lists) {
                    if (head) {
                        q.push(head -> val);
                        head = head -> next;
                    }
                    if (head) {
                        left = true;
                    }
                }
                f = left; // once f = false, no need to check the lists agagin
            }
            const int t = q.top();
            q.pop();
            if (!head) {
                head = current = new ListNode(t);
                continue;
            }
            current = current -> next = new ListNode(t);
        }
        return head;
    }
    
};

// 40ms, 12.5MB