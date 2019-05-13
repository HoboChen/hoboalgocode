class Solution {
private:
    
    vector<vector<int>> dp;
    vector<bool> star;
    
    int f(const string& s, const string& p, int i, int j) {
        if (j == -1) {
            return i == -1;
        }
        if (i == -1) {
            return star[j];
        }
        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        if (p[j] == '?' && i >= 0) {
            return dp[i][j] = f(s, p, i - 1, j - 1);
        }
        if (p[j] == '*') {
            for (int k = i; k >= -1; k--) {
                if (f(s, p, k, j - 1)) {
                    return dp[i][j] = 1;
                }
            }
            return dp[i][j] = 0;
        }
        if (p[j] == s[i]) {
            return dp[i][j] = f(s, p, i - 1, j - 1);
        }
        return dp[i][j] = 0;
    }
    
public:
    bool isMatch(string s, string p) {
        dp = vector<vector<int>>(s.size() + 1, vector<int>(p.size() + 1, -1));
        star = vector<bool>(s.size(), 0);
        int pos = 0;
        while (s[pos] == '*') {
            star[pos++] = 1;
        }
        return f(s, p, s.size() - 1, p.size() - 1);
    }
};

// 130ms, 30.6MB