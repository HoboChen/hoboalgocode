class Solution {
private:
    inline bool check(vector<ListNode*>& cur) {
        for (int i = 0; i < cur.size(); i++)
            if (cur[i]) return 1;
        return 0;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<ListNode*> cur;
        for (int i = 0; i < lists.size(); i++)
            cur.push_back(lists[i]);
        ListNode* ret = new ListNode(0);
        ListNode* curt = ret;
        priority_queue<pair<int, int> > q;
        for (int i = 0; i < cur.size(); i++) {
            if (cur[i]) {
                int t = cur[i] -> val;
                q.push(make_pair(-t, i));
                cur[i] = cur[i] -> next;
            }
        }
        while (check(cur)) {
            pair<int, int> t = q.top();
            q.pop();
            curt -> next = new ListNode(-t.first);
            curt = curt -> next;
            if (cur[t.second]) {
                q.push(make_pair(0 - cur[t.second] -> val, t.second));
                cur[t.second] = cur[t.second] -> next;
            }
        }
        while (!q.empty()) {
            pair<int, int> t = q.top();
            q.pop();
            curt -> next = new ListNode(-t.first);
            curt = curt -> next;
        }
        return ret -> next;
    }
};