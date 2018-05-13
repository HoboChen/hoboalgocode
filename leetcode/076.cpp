
class Solution {
private:
    static int maxn = 128; // size of char
    int cnt[maxn], tcnt, c[maxn], v[maxn], vcnt; // vcnt means cnt of char already satisfied
    bool vis[maxn], f;

public:     
    string minWindow(string s, string t) {
        memset(cnt, 0, sizeof(cnt));
        tcnt = 0;
        for (int i = 0; i < t.size(); i++) cnt[t[i]]++;
        for (int i = 0; i < maxn; i++) if (cnt[i]) tcnt++;
        int i = 0, j = 0; 

        string ret;
        for (i = 0; i < s.size(); i++) {
            memset(vis, 0, sizeof(vis));
            memset(v, 0, sizeof(v));
            f = vcnt = 0;
            j = i;
            while (j < s.size()) { // get satisfied j
                v[s[j]]++;
                if (vis[s[j]] != 1 && v[s[j]] == cnt[s[j]] && cnt[s[j]]) { vcnt++; vis[s[j]] = 1; }
                if (vcnt == tcnt) { f = 1; break; }
                j++;
            }
            if (!f && j >= s.size() - 1) return ret; // has no better solution
            while (f && v[s[i]] > cnt[s[i]]) v[s[++i]]--; // get better i
            if (f && j - i + 1 < ret.size() || ret == "")
                ret = s.substr(i, j - i + 1);
            i++;
            while ((cnt[s[i]]) == 0 && i < s.size()) i++;
            i--;
        }
        return ret;
    }
};
