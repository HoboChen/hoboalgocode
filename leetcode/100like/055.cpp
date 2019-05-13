class Solution {

public:
    bool canJump(vector<int>& nums) {
        int can = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i > can) {
                break;
            }
            can = max(can, i + nums[i]);
        }
        return can >= nums.size() - 1;
    }
};

// 20ms, 9.9MB