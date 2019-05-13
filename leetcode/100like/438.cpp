class Solution {
private:
    int cnt_s[256];
    int cnt_p[256];
    
    bool valid() {
        for (int i = 0; i < 256; i++) {
            if (cnt_s[i] < cnt_p[i]) {
                return false;
            }
        }
        return true;
    }
    
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.empty() || p.empty() || s.size() < p.size()) {
            return {};
        }
        memset(cnt_s, 0, sizeof(cnt_s));
        memset(cnt_p, 0, sizeof(cnt_p));
        vector<int> ans;
        for (auto c : p) {
            cnt_p[c]++;
        }
        for (int i = 0; i < p.size() - 1; i++) {
            cnt_s[s[i]]++;
        }
        for (int i = 0; i < s.size() - p.size() + 1; i++) {
            cnt_s[s[i + p.size() - 1]]++;
            if (valid()) {
                ans.push_back(i);
            }
            cnt_s[s[i]]--;
        }
        return ans;
    }
};

// 76ms, 10.2MB