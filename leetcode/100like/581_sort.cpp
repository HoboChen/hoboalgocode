class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int l = 0;
        int r = 0;
        vector<int> p = nums;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < p.size(); i++) {
            if (p[i] != nums[i]) {
                l = i;
                break;
            }
        }
        for (int i = p.size() - 1; i >= 0; i--) {
            if (p[i] != nums[i]) {
                r = i;
                break;
            }
        }
        return r == l ? 0 : r - l + 1;
    }
};

// 48ms, 11.4MB