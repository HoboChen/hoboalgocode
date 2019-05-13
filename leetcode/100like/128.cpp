class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> bucket(nums.begin(), nums.end());
        int ans = 0;
        for (auto x : bucket) {
            int cnt = 1;
            int cur = x;
            while (bucket.find(++cur) != bucket.end()) {
                bucket.erase(cur);
                cnt++;
            }
            cur = x;
            while (bucket.find(--cur) != bucket.end()) {
                bucket.erase(cur);
                cnt++;
            }
            ans = max(ans, cnt);
        }
        return ans;
    }
};

// 12ms, 9.9MB