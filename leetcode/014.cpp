class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string ret = "";
        int len = 0;
        if (strs.size() < 1) return ret;
        while (len < strs[0].size()) {
            char next = strs[0][len];
            bool ok = 1;
            for (int i = 1; i < strs.size(); i++) {
                if (len >= strs[i].size()) ok = 0;
                if (strs[i][len] != next) ok = 0;
                if (!ok) break;
            }
            len++;
            if (ok) ret.push_back(next);
            if (!ok) break;
        }
        return ret;
    }
};