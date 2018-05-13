class Solution {
private:
    ListNode *apend;
public:
    inline int listLen(ListNode* l) {
        int res = 1;
        ListNode* tmp = l;
        while (tmp -> next) {
            tmp = tmp -> next;
            res++;
        }
        return res;
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int lena = listLen(l1);
        int lenb = listLen(l2);

        if (lena < lenb) {
            swap(l1, l2);
            swap(lena, lenb);
        }
        ListNode *pos1 = l1, *pos2 = l2;
        int d = 0;
        bool f1 = 1;
        for (int i = 0; i < lena; i++) {
            int t;
            if (f1) t = pos2 -> val;
            else t = 0;
            pos1 -> val += t + d;
            d = pos1 -> val / 10;
            pos1 -> val %= 10;
            if (pos2 -> next) pos2 = pos2 -> next;
            else f1 = 0;
            if (pos1 -> next) pos1 = pos1 -> next;
        }
        if (d > 0) {
            apend = new ListNode(d);
            pos1 -> next = apend;
            pos1 -> next -> next = 0;
        }
        return l1;
    }
};