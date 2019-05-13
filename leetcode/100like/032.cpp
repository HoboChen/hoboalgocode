class Solution {
private:
    
    vector<int> dp;
    
    int f(const string& s, int i) {
        if (i <= 0 || s[i] == '(') {
            return 0;
        }
        if (dp[i]) {
            return dp[i];
        }
        if (s[i - 1] == '(') {
            return dp[i] = f(s, i - 2) + 2;
        }
        if (i - f(s, i - 1) > 0 && s[i - f(s, i - 1) - 1] == '(') {
            if (i - f(s, i - 1) > 1) {
                return dp[i] = f(s, i - 1) + f(s, i - f(s, i - 1) - 2) + 2;
            }
            return dp[i] = f(s, i - 1) + 2;
        }
        return 0;
    }
    
public:
    int longestValidParentheses(string s) {
        if (!s.size()) {
            return 0;
        }
        dp = vector<int>(s.size(), 0);
        int ans = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            f(s, i);
        }
        for (const auto t : dp) {
            ans = max(ans, t);
        }
        return ans;
    }
};

// 12ms, 9.9MB