class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        stack<int> s;
        for (int i = 0; i < height.size(); i++) {
            while (!s.empty() && height[i] > height[s.top()]) {
                int top = s.top();
                s.pop();
                if (s.empty()) {
                    break;
                }
                int width = i - s.top() - 1;
                ans += width * (min(height[i], height[s.top()]) - height[top]);
            }
            s.push(i);
        }
        return ans;
    }
};

// 8ms, 9.3MB