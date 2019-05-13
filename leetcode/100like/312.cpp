class Solution {
private:
    
    vector<vector<int>> dp;
    
    int f(const vector<int>& nums, int i, int j) {
        if (i + 1 >= j) {
            return 0;
        }
        if (dp[i][j]) {
            return dp[i][j];
        }
        if (i + 2 == j) {
            return dp[i][j] = nums[i] * nums[i + 1] * nums[j];
        }
        int ans = 0;
        for (int k = i + 1; k < j; k++) {
            int t = nums[i] * nums[k] * nums[j] + f(nums, i, k) + f(nums, k, j);
            ans = max(ans, t);
        }
        return dp[i][j] = ans;
    }
    
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        dp = vector<vector<int>>(nums.size(), vector<int>(nums.size(), 0));
        return f(nums, 0, dp.size() - 1);
    }
};

// 32ms, 9.3MB