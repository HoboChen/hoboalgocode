class Solution {
private:
    
    vector<int> dp;
    
    int f(int k) {
        if (k == 1 || k == 2) {
            return k;
        }
        if (dp[k]) {
            return dp[k];
        }
        return dp[k] = f(k - 1) + f(k - 2);
    }
public:
    
    int climbStairs(int n) {
        dp = vector<int>(n + 1, 0);
        return f(n);
    }
};

// 4ms, 8.8MB