class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }
        vector<vector<vector<int> > > dp(prices.size(), vector<vector<int > >(2, vector<int>(3, 0)));        
        dp[0][1][0] = -prices[0];
        dp[0][1][1] = -prices[0];
        dp[0][1][2] = -prices[0];
        for (int i = 1; i < prices.size(); i++) {
            for (int j = 0; j < 3; j++) {
                dp[i][0][j] = dp[i - 1][0][j];
                dp[i][1][j] = max(dp[i - 1][0][j] - prices[i], dp[i - 1][1][j]);
            }
            for (int j = 1; j < 3; j++) {
                dp[i][0][j] = max(dp[i][0][j], dp[i - 1][1][j - 1] + prices[i]);
            }
        }
        return dp[prices.size() - 1][0][2];
    }
};
