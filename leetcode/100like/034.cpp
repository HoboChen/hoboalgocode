class Solution {
public:
    int lower(vector<int>& n, int target) {
        int l = 0;
        int r = n.size();
        int ans = -1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (n[mid] < target) {
                l = mid + 1;
            }
            else {
                r = mid;
                ans = mid;
            }
        }
        return ans != -1 && n[ans] == target ? ans : -1;
    }
    
    int upper(vector<int>& n, int target) {
        int l = 0;
        int r = n.size();
        int ans = -1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (n[mid] <= target) {
                l = mid + 1;
                ans = mid;
            }
            else { 
                r = mid;
            }
        }
        return ans != -1 && n[ans] == target ? ans : -1;
    }
    
    vector<int> searchRange(vector<int>& nums, int target) {
        return {
            lower(nums, target),
            upper(nums, target)};
    }
};

// 8ms, 10.2MB