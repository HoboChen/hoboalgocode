#include "leetcode.hpp"

using namespace std;

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
    
    struct triple{
        int a, b, c;
        bool operator < (const triple& x) const {
            if (a != x.a) return a < x.a;
            if (b != x.b) return b < x.b;
            return c < x.c;
        }
        triple(int a, int b, int c) : a(a), b(b), c(c) { }
        vector<int> ToVector() {
            vector<int> ret;
            ret.push_back(a);
            ret.push_back(b);
            ret.push_back(c);
            // sort(ret.begin(), ret.end());
            return ret;
        }
    };
    
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        unordered_map<int, vector<int> > m;
        int p = 0;
        for (auto x : nums) m[x].push_back(p++);
        set<triple> ret;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < nums.size(); j++) {
                if (i == j) continue;
                bool ok = 0;
                if (m.find(-nums[i] - nums[j]) != m.end()) {
                    vector<int>& it = m[-nums[i] - nums[j]];
                    for (auto x : it) {
                        if (x != i && x != j)
                            ok = 1;
                    }
                }
                if (ok) ret.insert(triple(nums[i], nums[j], -nums[i] - nums[j]));
            }
        }
        vector<vector<int>> retv;
        for (auto x : ret) retv.push_back(x.ToVector());
        return retv;
    }
};


int main() {

    return 0;
}