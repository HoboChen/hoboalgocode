class Solution {
    
private:
    bool nextPermutation(vector<int>& nums) {
        int i = 0;
        for (i = nums.size() - 1; i >= 1; i--) {
            if (nums[i] > nums[i - 1]) {
                break;
            }
        }
        if (i == 0) {
            return false;
        }
        int j = i;
        for (int k = i; k < nums.size(); k++) {
            if (nums[k] > nums[i - 1]) {
                j = k;
            }
        }
        swap(nums[i - 1], nums[j]);
        reverse(nums.begin() + i, nums.end());
        return true;
    }
    
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        ans.push_back(nums);
        while (nextPermutation(nums)) {
            ans.push_back(nums);
        }
        return ans;
    }
};

// 12ms, 9.1MB