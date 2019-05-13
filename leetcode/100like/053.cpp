class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> m(nums.size(), 0);
        int ans = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            m[i] = i == 0 ? nums[i] : max({nums[i], nums[i] + m[i - 1]});
            ans = max(ans, m[i]);
        }
        return ans;
    }
};

// 8ms, 9.3MB