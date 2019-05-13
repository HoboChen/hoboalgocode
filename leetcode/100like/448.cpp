class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> ret;
        for (int i = 0; i < nums.size(); i++) {
            int t = nums[i];
            nums[abs(t) - 1] = -abs(nums[abs(t) - 1]);
        }
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) {
                ret.push_back(i + 1);
            }
        }
        return ret;
    }
};

// 116ms, 14.9MB