class Solution {
private:
    int backpack(const vector<int>& nums, int s) {
        int dp[2][s + 1];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j <= s; j++) {
                dp[i % 2][j] = dp[(i + 1) % 2][j];
                if (j >= nums[i]) {
                dp[i % 2][j] = max(
                    dp[i % 2][j],
                    dp[(i + 1) % 2][j - nums[i]] + nums[i]);    
                }
            }
        }
        return dp[(nums.size() + 1) % 2][s];
    }
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        return sum % 2 == 0 && backpack(nums, sum / 2) == sum / 2;
    }
};

// 124ms, 8.3MB