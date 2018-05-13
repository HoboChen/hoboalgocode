
// TLE
class Solution {
private:
    vector<int> _3Int2Vector(int a, int b, int c) {
        vector<int> ret;
        ret.reserve(3);
        ret.push_back(a);
        ret.push_back(b);
        ret.push_back(c);
        sort(ret.begin(), ret.end());
        return ret;
    }
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        set<vector<int> > ret;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (i == j) continue;
                int tar = -nums[i] - nums[j];
                int num = upper_bound(nums.begin(), nums.end(), tar) - lower_bound(nums.begin(), nums.end(), tar);
                if (num == 0) continue;
                if (nums[i] == nums[j] && nums[i] == tar && num < 3) continue;
                else {
                    if (nums[i] == tar && num < 2) continue;
                    if (nums[j] == tar && num < 2) continue;
                }
                ret.insert(_3Int2Vector(nums[i], nums[j], tar));
            }
        }
        vector<vector<int> > retv(ret.begin(), ret.end());
        return retv;
    }
};