class Solution {
private:
    vector<int> dp;
    set<string> dict;
    
    int f(const string& s, int i) {
        if (i == 0) {
            return 1; // true
        }
        if (dp[i] != -1) {
            return dp[i];
        }
        for (const auto& word : dict) {
            if (i >= word.size()) {
                if (s.substr(i - word.size(), word.size()) == word && 
                        f(s, i - word.size())) {
                    return dp[i] = true;
                }
            }
        }
        return dp[i] = false;
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        dict = set<string>(wordDict.begin(), wordDict.end());
        dp = vector<int>(s.size() + 1, -1);
        return f(s, s.size());
    }
};

// 8ms, 8.8MB