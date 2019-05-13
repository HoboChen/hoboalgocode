// TLE

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
        unordered_multiset<int> m;
        int p = 0;
        for (auto x : nums) m.insert(x);
        set<vector<int> > ret;
        if (nums.size() < 3) {
            vector<vector<int>> tmp;
            return tmp;
            
        }
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < nums.size(); j++) {
                if (i == j) continue;
                bool ok = 1;
                if (m.count(-nums[i] - nums[j]) == 0) continue;
                if (-nums[i] - nums[j] == nums[i] && m.count(nums[i]) < 2) ok = 0;
                if (-nums[i] - nums[j] == nums[j] && m.count(nums[j]) < 2) ok = 0;
                if (nums[i] == nums[j] && -nums[i] - nums[j] == nums[i] && m.count(nums[i]) < 3) ok = 0;
                if (ok) ret.insert(_3Int2Vector(nums[i], nums[j], -nums[i] - nums[j]));
            }
        }
        vector<vector<int> > retv(ret.begin(), ret.end());
        return retv;
    }
};