#include <bits/stdc++.h>

using namespace std;

int dp[1000 + 10][100 + 10]; // dp[i][j] means there is i space left, and current in jth

int main() {
    int t, m;
    cin >> t >> m;
    vector<int> value(m + 1, 0);
    vector<int> size(m + 1, 0);
    
    for (int i = 1; i <= m; i++) {
        cin >> size[i] >> value[i];
    }
    for (int i = 1; i <= m; i++) {
        for (int j = t; j >= size[i]; j--) {
            dp[j][i] = max(dp[j][i], dp[j][i - 1]);
            dp[j - size[i]][i] = max(dp[j - size[i]][i - 1], dp[j][i - 1] + value[i]);
        }
    }
    int ans = -1;
    for (int i = 0; i <= t; i++) {
        ans = max(ans, dp[i][m]);
    }
    cout << ans << endl;
    return 0;
}