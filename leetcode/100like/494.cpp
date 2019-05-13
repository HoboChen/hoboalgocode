class Solution {
private:
    int s;
    int ans;
    
    void dfs(const vector<int>& nums, int i, int sum) {
        if (i == nums.size()) {
            if (sum == s) {
                ans++;
            }
            return;
        }
        dfs(nums, i + 1, sum + nums[i]);
        dfs(nums, i + 1, sum - nums[i]);
    }
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        s = S;
        ans = 0;
        dfs(nums, 0, 0);
        return ans;
    }
};

// 1240ms, 8.2MB