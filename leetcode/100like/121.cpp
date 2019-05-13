class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int m = INT_MAX;
        int ans = 0;
        for (const auto price : prices) {
            m = min(price, m);
            ans = max(price - m, ans);
        }
        return ans;
    }
};

// 8ms, 9.4MB