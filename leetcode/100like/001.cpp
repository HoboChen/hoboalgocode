class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> m;
        for (int i = 0; i < nums.size(); i++) {
            const int complement = target - nums[i];
            if (m.find(complement) != m.end()) {
                return vector<int>{m[complement], i};
            }
            m[nums[i]] = i;
        }
        return vector<int>();
    }
};

// 12ms, 10.3MB