class Solution {
private:
    
    vector<vector<int>> dp;
    
    int f(const string& s, const string& p, int i, int j) {
        if (i == -1 || j == -1) {
            return abs(i - j);
        }
        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        if (s[i] == p[j]) {
            return dp[i][j] = f(s, p, i - 1, j - 1);
        }
        return dp[i][j] = min({
            f(s, p, i - 1, j),
            f(s, p, i, j - 1),
            f(s, p, i - 1, j - 1)}) + 1;
    }
    
public:
    int minDistance(string word1, string word2) {
        dp = vector<vector<int>>(word1.size(), vector<int>(word2.size(), -1));
        return f(word1, word2, word1.size() - 1, word2.size() - 1);
    }
};

// 12ms, 11.7MB