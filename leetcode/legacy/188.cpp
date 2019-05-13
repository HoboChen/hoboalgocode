class Solution {
public:

    int maxProfitNoLimit(vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }
        vector<vector<int> > dp(prices.size(), vector<int>(2, 0));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = max(dp[i - 1][1] + prices[i], dp[i - 1][0]);
            dp[i][1] = max(dp[i - 1][0] - prices[i], dp[i - 1][1]);
        }
        return dp[prices.size() - 1][0];
    }

    int maxProfit(int k, vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }
        int n = prices.size();
        if (n < k) {
            return maxProfitNoLimit(prices);
        }
        vector<vector<vector<int> > > dp(2, vector<vector<int > >(2, vector<int>(min(n, k) + 1, 0)));        
        for (int i = 0; i < min(n, k) + 1; i++) {
            dp[0][1][i] = -prices[0];
        }
        for (int i = 1; i < prices.size(); i++) {
            for (int j = 0; j < min(n, k) + 1; j++) {
                dp[i % 2][0][j] = dp[(i + 1) % 2][0][j];
                dp[i % 2][1][j] = max(dp[(i + 1) % 2][0][j] - prices[i], dp[(i + 1) % 2][1][j]);
            }
            for (int j = 1; j < min(n, k) + 1; j++) {
                dp[i % 2][0][j] = max(dp[i % 2][0][j], dp[(i + 1) % 2][1][j - 1] + prices[i]);
            }
        }
        return dp[(prices.size() + 1) % 2][0][min(n, k)];
    }
};
