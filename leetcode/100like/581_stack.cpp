class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int l = nums.size() - 1;
        int r = 0;
        stack<int> s;
        for (int i = 0; i < nums.size(); i++) {
            while (!s.empty() && nums[i] < nums[s.top()]) {
                l = min(l, s.top());
                s.pop();
            }
            s.push(i);
        }
        s = stack<int>();
        for (int i = nums.size() - 1; i >= 0; i--) {
            while (!s.empty() && nums[i] > nums[s.top()]) {
                r = max(r, s.top());
                s.pop();
            }
            s.push(i);
        }
        return r - l <= 0 ? 0 : r - l + 1;
    }
};

36ms, 11.7MB