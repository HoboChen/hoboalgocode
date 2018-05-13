class Solution {
private:
    vector<int> _3Int2Vector(int a, int b, int c) {
        vector<int> ret;
        ret.push_back(a);
        ret.push_back(b);
        ret.push_back(c);
        sort(ret.begin(), ret.end());
        return ret;
    }
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ret;
        sort(nums.beign(), nums.end());
        for (int i = 0; i < n; i++) {
            int l = i + 1, r = nums.size() - 1;
            while (l < r) {
                while (nums[l] + nums[r - 1] + nums[i] > 0 && r > l) r--;
                if (nums[l] + nums[r] + nums[i] == 0) {
                    ret.push_back(_3Int2Vector(nums[i], nums[l], nums[r]));
                }
                l++;
            }
        }
        return ret;
    }
};