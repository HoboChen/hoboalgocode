class Solution {
private:
    
    vector<vector<int>> dp;
    
    inline bool f(const string& s, const string& p, int i, int j) {
        if (dp[i][j] != -1) {
            return dp[i][j] == 1;
        }
        if (j == p.size()) {
            return dp[i][j] = i == s.size();
        }
        bool m = i < s.size() && (s[i] == p[j] || p[j] == '.');
        if (j + 1 < p.size() && p[j + 1] == '*') {
            return dp[i][j] = f(s, p, i, j + 2) || (m && f(s, p, i + 1, j));
        } else {
            return dp[i][j] = m && f(s, p, i + 1, j + 1);
        }
        return dp[i][j] = 0;
    }
    
public:
    bool isMatch(string s, string p) {
        dp = vector<vector<int>>(s.size() + 1, vector<int>(p.size() + 1, -1));
        return f(s, p, 0, 0);
    }
};

// 8ms, 11.7MB