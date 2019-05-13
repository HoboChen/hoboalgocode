class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<array<int, 3>> answers;
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                const int target = -nums[i] - nums[j];
                auto k = lower_bound(nums.begin() + j + 1, nums.end(), target) - nums.begin();
                if (k < nums.size() && nums[k] == target) {
                    answers.insert({nums[i], nums[j], nums[k]});
                }
            }
        }
        ret.reserve(answers.size());
        for (auto v : answers) {
            ret.push_back({v[0], v[1], v[2]});
        }
        return ret;
    }
};

// 1104ms, 17.9MB