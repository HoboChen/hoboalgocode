class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        vector<int> maxD(nums.size(), 0);
        vector<int> minD(nums.size(), 0);
        int ans = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            maxD[i] = i == 0 ? nums[i] : max({nums[i], maxD[i - 1] * nums[i], minD[i - 1] * nums[i]});
            minD[i] = i == 0 ? nums[i] : min({nums[i], maxD[i - 1] * nums[i], minD[i - 1] * nums[i]});
            ans = max({ans, maxD[i], minD[i]});
        }
        return ans;
    }
};

// 12ms, 9.3MB