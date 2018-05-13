class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> m;
        vector<int> ret;
        for (int i = 0; i < nums.size(); i++) {
            m[nums[i]] = i;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (m.find(target - nums[i]) != m.end() && m[target - nums[i]] != i) {
                ret.push_back(i);
                ret.push_back(m[target - nums[i]]);
                return ret;
            }
        }
        return ret;
    }
};