class Solution {
    
private:
    
    int mLength;
    vector<string> mAnswer;
    
    void DFS(const string& s) {
        int count[2];
        count[0] = count[1] = 0;
        for (const auto c : s) {
            if (c == ')') {
                count[1]++;
            } else {
                count[0]++;
            }
        }
        if (count[0] == count[1] && s.size() == mLength * 2) {
            mAnswer.push_back(s);
            return;
        }
        if (count[1] > count[0] || count[0] > mLength) {
            return;
        } else if (count[0] == count[1]) {
            DFS(s + "(");
        } else {
            DFS(s + "(");
            DFS(s + ")");
        }
    }
    
public:
    
    Solution() : mLength(0) { }
    
    vector<string> generateParenthesis(int n) {
        mLength = n;
        DFS("");
        return mAnswer;
    }
};

// 20ms, 18.7MB