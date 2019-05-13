class Solution {
public:
    int search(vector<int>& nums, int k) {
        int l = 0;
        int r = nums.size() - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == k) {
                return mid;
            }
            if (nums[mid] < nums[r]) { // [mid, r] is sorted
                if (nums[mid] < k && k <= nums[r]) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            } else { // [l, mid] is sorted
                if (nums[l] <= k && k < nums[mid]) {
                    r = mid - 1;
                }
                else {
                    l = mid + 1;
                }
            }
        }
        return -1;
    }
};

// 4ms, 8.6MB