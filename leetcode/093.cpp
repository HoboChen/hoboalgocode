class Solution {
private:
    inline bool valid(string s) {
        if (s[0] == '0' && s.size() > 1) return 0;
        int val = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            val *= 10;
            val += s[i] - '0';
        }
        return val <= 255;
    }
    void dfs(vector<string>& ret, string s, int pos, int dep, string cur) {
        if (dep > 4) return;
        if (dep == 4 && pos == s.size()) {
            ret.push_back(cur);
            return;
        }
        for (int len = 1; len <= min(3, (int)s.size() - pos); len++) {
            if (valid(s.substr(pos, len))) {
                dfs(ret, s, pos + len, dep + 1, cur + (dep != 0 ? "." : "") + s.substr(pos, len));
            }
        }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> ret;
        dfs(ret, s, 0, 0, "");
        return ret;
    }
};