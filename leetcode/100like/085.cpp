class Solution {
private:
    int largestRectangleArea(vector<int>& height) {
        stack<int> s;
        int ans = 0;
        for (int i = 0; i < height.size(); i++) {
            while (!s.empty() && height[i] < height[s.top()]) {
                int top = s.top();
                s.pop();
                int width = i - (s.empty() ? 0 : s.top() + 1);
                ans = max(ans, height[top] * width);
            }
            s.push(i);
        }
        while (!s.empty()) {
            int top = s.top();
            s.pop();
            int width = height.size() - (s.empty() ? 0 : s.top() + 1);
            ans = max(ans, height[top] * width);
        }
        return ans;
    }
public:
    
    int maximalRectangle(vector<vector<char>>& matrix) {
        int ans = 0;
        if (matrix.empty()) {
            return ans;
        }
        vector<vector<int>> m(matrix.size(), vector<int>(matrix[0].size()));
        for (int j = 0; j < matrix[0].size(); j++) {
            m[0][j] = matrix[0][j] == '0' ? 0 : 1;
            for (int i = 1; i < matrix.size(); i++) {
                if (matrix[i][j] == '0') {
                    m[i][j] = 0;
                } else {
                    m[i][j] = m[i - 1][j] + 1;
                }
            }
        }
        for (int i = 0; i < matrix.size(); i++) {
            ans = max(ans, largestRectangleArea(m[i]));
        }
        return ans;
    }
    
};

// 32ms, 12MB