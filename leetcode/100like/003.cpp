class Solution {
public:
    int lengthOfLongestSubstring(string rawStr) {
        map<char, int> s;
        int ans = 0;
        int i = 0;
        int j = 0;
        while (i < rawStr.size() && j < rawStr.size()) {
            if (s.find(rawStr[j]) == s.end()) {
                s[rawStr[j]] = j;
                ans = max(ans, j - i + 1);
                j++;
            } else {
                i = s[rawStr[j]] + 1;
                j = i;
            }
        }
        return ans;
    }
};

// 52ms, 21.1MB