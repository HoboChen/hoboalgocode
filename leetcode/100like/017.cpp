class Solution {
private:
    map<char, string> table;
    
public:
    
    Solution() { 
        table = map<char, string>{
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}};
    }
    
    vector<string> letterCombinations(string digits) {
        vector<string> tmp;
        for (const auto c : digits) {
            auto t = tmp;
            if (t.empty()) {
                for (const auto d : table[c]) {
                    tmp.push_back(string{d});
                }
            } else {
                for (const auto s : t) {
                    for (const auto d : table[c]) {
                        tmp.push_back(s + string({d}));
                    }
                }
            }
        }
        vector<string> answer;
        for (const auto s : tmp) {
            if (s.size() == digits.size()) {
                answer.push_back(s);
            }
        }
        return answer;
    }
};

// 4ms, 8.9MB