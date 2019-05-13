class Solution {
private:
    
    constexpr static int dx[4] = {0, 0, 1, -1};
    constexpr static int dy[4] = {1, -1, 0, 0};
    
    vector<vector<char>> mBoard;
    
    bool dfs(vector<vector<char>>& board, int i, int j, const string& word, int depth = 0) { 
        if (!(i >= 0 && j >= 0 && i < board.size() && j < board[i].size() && word[depth] == board[i][j])) {
            return false;
        }
        if (depth == word.size() - 1) {
            return true;
        }
        board[i][j] = 0;
        for (int k = 0; k < 4; k++) {
            if (dfs(board, i + dx[k], j + dy[k], word, depth + 1)) {
                board[i][j] = mBoard[i][j];
                return true;
            }
        }
        board[i][j] = mBoard[i][j];
        return false;
    }
    
public:
    
    bool exist(vector<vector<char>>& board, string word) {
        mBoard = board;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (mBoard[i][j] != word[0]) {
                    continue;
                }
                vector<vector<char>> board_copy = mBoard;
                if (dfs(board_copy, i, j, word)) {
                    return true;
                }
            }
        }
        return false;
    }
};

// 80ms, 46.8MB