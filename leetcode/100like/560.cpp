class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int cnt = 0;
        map<int, int> q;
        q[0] = 1;
        for (int i = 1; i < nums.size(); i++) {
            nums[i] += nums[i - 1];
        }
        for (int i = 0; i < nums.size(); i++) {
            cnt += q[nums[i] - k];
            q[nums[i]] += 1;
        }
        return cnt;
    }
};

// 60ms, 18.5MB