class Solution {
private:
inline int calc(vector<int>& c, int k) {
    int ret = -1e7;
    set<int> s;
    s.insert(c[0]);
    for (int i = 1; i < c.size(); i++) {
        int p = *lower_bound(s.begin(), s.end(), c[i] - k);
        if (p >= c[i] - k) ret = max(ret, c[i] - p);
        s.insert(c[i]);
    }
    return ret;
}

vector<vector<int>> transpose(vector<vector<int>>& matrix) {
    vector<vector<int>> ret(matrix[0].size(), vector<int>(matrix.size(), 0));
    int n = matrix.size(), m = matrix[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ret[j][i] = matrix[i][j];
    return ret;
}

public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        
        if (matrix.size() > matrix[0].size()) matrix = transpose(matrix);
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> cc(n, vector<int>(m, 0));
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                if (i == 0) cc[i][j] = matrix[i][j];
                else cc[i][j] = cc[i - 1][j] + matrix[i][j];
            }
        }
        int ans = -1e7;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                vector<int> t(m, 0);
                for (int k = 0; k < m; k++) {
                    if (i == 0) t[k] = cc[j][k];
                    else t[k] = cc[j][k] - cc[i - 1][k];
                }
                vector<int> tc(m + 1, 0);
                tc[0] = 0;
                for (int l = 1; l <= m; l++)
                    tc[l] = tc[l - 1] + t[l - 1];
                ans = max(ans, calc(tc, k));
            }
        }
        return ans;
    }
};
