class Solution {
private:
    static const int SIZE = 9;
    inline bool isValidBlock(const vector<char>& inn) {
        set<char> tmp;
        for (auto x : inn) {
            if (x == '.') continue;
            if (tmp.find(x) == tmp.end()) 
                tmp.insert(x);
            else 
                return 0;
        }
        return 1;
    }
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool f = 1;
        for (int i = 0; i < board.size(); i++) { // row
            f = f && isValidBlock(board[i]);
        }
        for (int i = 0; i < SIZE; i++) { // column
            vector<char> tmp;
            for (int j = 0; j < SIZE; j++) {
                tmp.push_back(board[j][i]);
            }
            f = f && isValidBlock(tmp);
        }
        for (int i = 0; i < SIZE; i++) { // little 3x3 square
            vector<char> tmp;
            int r = i / 3, c = i % 3;
            r *= 3, c *= 3;
            for (int j = 0; j < SIZE; j++) {
                int dr = j / 3, dc = j % 3;
                tmp.push_back(board[r + dr][c + dc]);
            }
            f = f && isValidBlock(tmp);
        }
        return f;
    }
};