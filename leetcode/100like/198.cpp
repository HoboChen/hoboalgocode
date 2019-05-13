class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        vector<vector<int>> dp(nums.size(), vector<int>(2, 0));
        int len = nums.size();
        for (int i = 0; i < len; i++) {
            if (i == 0) {
                dp[i][0] = 0;
                dp[i][1] = nums[i];
                continue;
            }
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = dp[i - 1][0] + nums[i];
        }
        return max(dp[len - 1][0], dp[len - 1][1]);
    }
};

// 4ms, 8.6MB