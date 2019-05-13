class Solution {
public:
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
};

// 16ms, 10.3MB