#include "leetcode.h"

// 72ms

class Solution {
public:
    int leastBricks(vector<vector<int> >& wall) {
        unordered_multiset<int> all;
        for (int i = 0; i < wall.size(); i++) {
            for (int j = 1; j < wall[i].size(); j++) {
                wall[i][j] += wall[i][j - 1];
                all.insert(wall[i][j - 1]);
            }
        }
        int width = wall[0][wall[0].size() - 1];
        int ans = 1e7;
        for (auto x : all) {
            if (x != width) {
                int tmp = wall.size() - all.count(x);
                ans = min(ans, tmp);
            }
        }
        return min(ans, (int)wall.size());
    }
};