class Solution {
private:
    
    static const int maxn = 10000;
    
    vector<int> G[maxn];
    
    int dp[maxn];
    
    int longestPathInDAG(int from) {
        if (dp[from] != -1) {
            return dp[from];
        }
        int t = 1;
        for (int i = 0; i < G[from].size(); i++) {
            int to = G[from][i];
            t = max(t, longestPathInDAG(to) + 1);
        }
        return dp[from] = t;
    }
    
public:
    int lengthOfLIS(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[j] > nums[i]) {
                    G[i].push_back(j);
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            ans = max(ans, longestPathInDAG(i));
        }
        return ans;
    }
};

// 108ms, 57.2MB