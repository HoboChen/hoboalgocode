class Solution {
private:
    inline int query(double x, vector<int>& nums1, vector<int>& nums2) {
        int of1 = lower_bound(nums1.begin(), nums1.end(), x) - nums1.begin();
        int of2 = lower_bound(nums2.begin(), nums2.end(), x) - nums2.begin();
        return of1 + of2 + 2;
    }
    inline double getkth(int k, vector<int>& nums1, vector<int>& nums2) {
        double l = 0, r = 2e6, mid;
        while (r - l > 1e-5) {
            mid = l + (r - l) / 2.0;
            if (query(mid, nums1, nums2) > k)
                r = mid;
            else 
                l = mid;
        }
        return mid;
    }
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int sz = (nums1.size() + nums2.size()) / 2;
        if ((nums1.size() + nums2.size()) % 2 == 1) return getkth(sz + 2, nums1, nums2);
        return (getkth(sz + 2, nums1, nums2) + getkth(sz + 1, nums1, nums2)) / 2.0;
    }
};