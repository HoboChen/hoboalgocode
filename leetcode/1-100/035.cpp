class Solution {
private:
    
    int binarySearch(const vector<int>& n, int l, int r, int t) {
        while (l < r) {
            int m = l + (r - l) / 2;
            if (n[m] == t) {
                return m;
            } else if (n[m] > t) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }
    
public:
    int searchInsert(vector<int>& nums, int target) {
        return binarySearch(nums, 0, nums.size(), target);
    }
};

// 8ms, 8.8MB