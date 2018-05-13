class Solution {
public:
    string longestPalindrome(string s) {
        int dp[s.size() + 1][s.size() + 1];
        memset(dp, 0, sizeof(dp));
        string ret;
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i; j < s.size(); j++) {
                dp[i][j] = (s[i] == s[j]) && (j - i < 3 || dp[i + 1][j - 1]);
                if (dp[i][j])
                    if (j - i + 1 > ret.size())
                        ret = s.substr(i, j - i + 1);
            }
        }
        return ret;
    }
};