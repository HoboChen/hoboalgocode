class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i = 0;
        for (i = nums.size() - 1; i >= 1; i--) {
            if (nums[i] > nums[i - 1]) {
                break;
            }
        }
        if (i == 0) {
            reverse(nums.begin(), nums.end());
            return;
        }
        int j = i;
        for (int k = i; k < nums.size(); k++) {
            if (nums[k] > nums[i - 1]) {
                j = k;
            }
        }
        swap(nums[i - 1], nums[j]);
        reverse(nums.begin() + i, nums.end());
        return;
    }
};

// 8ms, 8.6MB