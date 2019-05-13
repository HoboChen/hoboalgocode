class Solution {
private:
    map<char, string> m;
    vector<string> ret;

    void dfs(string d, int dep, string cur) {
        if (dep == d.size() && cur.size()) {
            ret.push_back(cur);
            return;
        }
        for (int i = 0; i < m[d[dep]].size(); i++) {
            dfs(d, dep + 1, cur + m[d[dep]][i]);
        }
    }

    void generateMap() {
        m['2'] = "abc";
        m['3'] = "def";
        m['4'] = "ghi";
        m['5'] = "jkl";
        m['6'] = "mno";
        m['7'] = "pqrs";
        m['8'] = "tuv";
        m['9'] = "wxyz";
    }
public:
    vector<string> letterCombinations(string digits) {
        generateMap();
        dfs(digits, 0, "");
        return ret;
    }
};