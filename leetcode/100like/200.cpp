class Solution {
private:
    
    int answer;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    
    void dfs(vector<vector<char>>& g, int i, int j) {
        if (i < 0 || j < 0 || i >= g.size() || j >= g[i].size()) {
            return;
        }
        if (g[i][j] == '0') {
            return;
        }
        g[i][j] = '0';
        for (int k = 0; k < 4; k++) {
            dfs(g, i + dx[k], j + dy[k]);
        }
    }
    
public:
    int numIslands(vector<vector<char>>& grid) {
        answer = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    answer++;
                }
            }
        }
        return answer;
    }
};

// 24ms, 10.7MB