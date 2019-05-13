class Solution {
private:
    
    vector<int> dp;
    
    int h(int n) {
        if (n <= 1) {
            return 1;
        }
        if (dp[n]) {
            return dp[n];
        }
        int ret = 0;
        for (int i = 1; i <= n; i++) {
            ret += h(i - 1) * h(n - i);
        }
        return dp[n] = ret;
    }
public:
    int numTrees(int n) {
        dp = vector<int>(n + 1, 0);
        return h(n);
    }
};

// 8ms, 8.1MB