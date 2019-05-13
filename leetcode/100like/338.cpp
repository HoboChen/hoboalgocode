class Solution {
private:
    vector<int> dp;
    
    int f(int i) {
        if (i == 0 || i == 1) {
            return dp[i] = i;
        }
        if (dp[i]) {
            return dp[i];
        }
        if (i % 2 == 0) {
            return dp[i] = f(i / 2);
        }
        return dp[i] = f(i / 2) + 1;
    }
    
public:
    vector<int> countBits(int num) {
        dp = vector<int>(num + 1, 0);
        for (int i = 0; i <= num; i++) {
            f(i);
        }
        return dp;
    }
};

// 68ms, 10.1MB