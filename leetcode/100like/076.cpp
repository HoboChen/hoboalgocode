class Solution {
    
private:
    
    inline bool valid() {
        for (int i = 0; i < 256; i++) {
            if (cnt_s[i] < cnt_t[i]) {
                return false;
            }
        }
        return true;
    }
    
    int cnt_t[256];
    int cnt_s[256];
    
public:
    
    Solution() {
        memset(cnt_t, 0, sizeof(cnt_t));
        memset(cnt_s, 0, sizeof(cnt_s));
    }
    
    string minWindow(string s, string t) {
        int i = 0;
        int j = 0;
        string ans;
        for (const auto x : t) {
            cnt_t[x]++;
        }
        while (j < s.size()) {
            cnt_s[s[j]]++;
            while (valid()) {
                if (ans == "" || ans.size() > j - i + 1) {
                    ans = s.substr(i, j - i + 1);
                }
                cnt_s[s[i]]--;
                i++;
            }
            j++;
        }
        return ans;
    }
};

// 140ms, 18.4MB