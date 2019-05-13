class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, int> index;
        int cnt = 0;
        for (const auto& x : strs) {
            string t = x;
            sort(t.begin(), t.end());
            if (index.find(t) == index.end()) {
                index[t] = cnt++;
            }
        }
        vector<vector<string>> ret(cnt, vector<string>());
        for (const auto& x: strs) {
            string t = x;
            sort(t.begin(), t.end());
            ret[index[t]].push_back(x);
        }
        return ret;
    }
};

// 44ms, 16.8MB