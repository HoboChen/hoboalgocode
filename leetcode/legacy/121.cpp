class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }
        vector<int> dp(prices.size(), 0);
        dp[0] = prices[0];
        for (int i = 1; i < prices.size(); i++) {
            dp[i] = min(dp[i - 1], prices[i]);
        }
        int ret = 0;
        for (int i = 0; i < prices.size(); i++) {
            ret = max(ret, prices[i] - dp[i]);
        }
        return ret;
    }
};
