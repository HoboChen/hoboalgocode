class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int length = nums1.size() + nums2.size();
        vector<int> merged(length, 0);
        merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), merged.begin());
        if (length % 2 == 1) {
            return merged[length / 2];
        }
        return (merged[length / 2 - 1] + merged[length / 2]) / 2.0;
    }
};

// 40ms, 21.7MB