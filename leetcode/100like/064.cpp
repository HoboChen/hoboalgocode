class Solution {

private:
    
    vector<vector<int>> dp;
    
    int f(const vector<vector<int>>& g, int i, int j) {
        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        if (i == 0 && j == 0) {
            return dp[i][j] = g[i][j];
        }
        if (i == 0) {
            return dp[i][j] = f(g, i, j - 1) + g[i][j];
        }
        if (j == 0) {
            return dp[i][j] = f(g, i - 1, j) + g[i][j];
        }
        return dp[i][j] = min(f(g, i - 1, j), f(g, i, j - 1)) + g[i][j];
    }
    
public:
    int minPathSum(vector<vector<int>>& grid) {
        dp = vector(grid.size(), vector<int>(grid[0].size(), -1));
        return f(grid, grid.size() - 1, grid[0].size() - 1);
    }
};

// 12ms, 11.1MB