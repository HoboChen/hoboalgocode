class Solution {
private:
    
    vector<vector<int>> answer;
    
    inline void dfs(vector<int> q, vector<int>& nums, int d) {
        if (d == nums.size()) {
            answer.push_back(q);
            return;
        }
        dfs(q, nums, d + 1);
        q.push_back(nums[d]);
        dfs(q, nums, d + 1);
    }
    
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> q;
        dfs(q, nums, 0);
        return answer;
    }
};

// 12ms, 17.8MB