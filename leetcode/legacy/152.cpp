class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int mins, maxs, ans;
        ans = mins = maxs = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            int t1 = mins * nums[i];
            int t2 = maxs * nums[i];
            mins = min(nums[i], min(t1, t2));
            maxs = max(nums[i], max(t1, t2));
            ans = max(ans, maxs);
        }
        return ans;
    }
};
