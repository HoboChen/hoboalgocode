class Solution {
    
private:
    
    bool f(const string& s, int i, int j) {
        if (dp[i][j] != -1) {
            return dp[i][j] == 1;
        }
        if (i > j || i >= s.size() || j < 0) {
            return false;
        }
        if (i == j) {
            return dp[i][j] = 1;
        }
        if (s[i] == s[j]) {
            if (i + 1 == j) {
                return dp[i][j] = 1;
            }
            return dp[i][j] = (int)f(s, i + 1, j - 1);
        }
        return dp[i][j] = false;
    }
    
    string mAnswer;
    vector<vector<int>> dp; // -1, 0 -> false, 1 -> true
    
public:
    string longestPalindrome(string s) {
        dp = vector<vector<int>>(s.size(), vector<int>(s.size(), -1));
        for (int i = 0; i < s.size(); i++) {
            for (int j = i; j < s.size(); j++) {
                if (f(s, i, j) && j - i + 1 > mAnswer.size()) {
                    mAnswer = s.substr(i, j - i + 1);
                }
            }
        }
        return mAnswer;
    }
};

// 316ms, 194.1MB