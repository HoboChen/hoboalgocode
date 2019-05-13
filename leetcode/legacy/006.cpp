class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1 || numRows >= s.size()) return s;
        vector<string> ans(numRows, "");
        string ret = "";
        int dir = 1; // 1 means down, -1 means up
        int cur = 0;
        for (char x : s) {
            ans[cur].push_back(x);
            cur = cur + dir;
            if (cur == numRows) {
                dir = -1;
                cur = cur - 2;
            }
            if (cur == 0)
                dir = 1;
        }
        for (auto x : ans)
            ret = ret + x;
        return ret;
    }
};