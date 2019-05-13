class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() == 0) return 0;
        map<char, int> lastPos;
        int i = 0, j = 0, ret = 0;
        while (j < s.size()) {
            while (lastPos.count(s[j]) == 0 && j < s.size()) {
                lastPos[s[j]] = j;
                j++;
            }
            ret = max(ret, j - i);
            if (j >= s.size()) break;
            i = j = lastPos[s[j]] + 1;
            lastPos.clear();
        }
        return max(ret, 1);
    }
};