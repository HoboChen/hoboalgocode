class Solution {
private:
    
    vector<vector<int>> dp;
    
    inline int f(int i, int j) {
        if (i <= 1 || j == 0 || i == j) {
            return dp[i][j] = 1;
        }
        if (dp[i][j]) {
            return dp[i][j];
        }
        return dp[i][j] = f(i - 1, j - 1) + f(i - 1, j);
    }

    inline int C(int k, int n) {
        dp = vector<vector<int>>(n + 2, vector<int>(n + 2, 0));
        return f(n, k);
    }
    
public:
    
    int uniquePaths(int m, int n) {
        return C(min(n, m) - 1, n + m - 2);
    }
    
};

// 8ms, 9.3MB