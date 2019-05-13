class Solution {
public:
    void sortColors(vector<int>& nums) {
        int i = 0, j = nums.size() - 1;
        for (int k = 0; k < nums.size(); k++) {
            if (nums[k] == 0) {
                i++;
            }
            if (nums[k] == 2) {
                if (j > 0) {
                    swap(nums[k], nums[j - 1]);
                }
            }
            if (nums[k] == 1) {
                swap(nums[k], nums[j]);
                j--;
            }
        }
    }
};

// 4ms, 8.6MB
