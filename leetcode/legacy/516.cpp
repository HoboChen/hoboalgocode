class Solution {
private:
    static const int maxn = 1000;
    int dp[maxn][maxn];
    
    template<typename _t>
    inline _t max(_t x, _t y, _t z) {
        return std::max(std::max(x, y), std::max(y, z));
    }
    int f(int l, int r, const string& s) {
        if (dp[l][r]) return dp[l][r];
        if (l == r) return dp[l][r] = 1;
        if (l + 1 == r) {
            if (s[l] == s[r]) return dp[l][r] = 2;
            else return dp[l][r] = 1;
        }
        if (s[l] == s[r]) return dp[l][r] = max(f(l + 1, r, s), f(l, r - 1, s), f(l + 1, r - 1, s) + 2);
        return dp[l][r] = max(f(l + 1, r, s), f(l, r - 1, s), f(l + 1, r - 1, s));
    }

public:
    int longestPalindromeSubseq(string s) {
        memset(dp, 0, sizeof(dp));
        return f(0, s.size() - 1, s);
    }
};