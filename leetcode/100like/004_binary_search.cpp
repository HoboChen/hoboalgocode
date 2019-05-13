class Solution {
private:
    
    const double eps = 2.2e-10;
    
    template <typename T1, typename T2>
    inline auto calcIndex(const vector<T1>& container, const T2 value) {
        return lower_bound(container.begin(), container.end(), value) - container.begin();
    }
    
    template <typename T1, typename T2>
    auto getKth(const vector<T1>& nums1, const vector<T2>& nums2, const int k) {
        double l = -INT_MAX;
        double r = INT_MAX;
        while (l < r - eps) {
            double mid = (l + r) / 2;
            auto idx1 = calcIndex(nums1, mid);
            auto idx2 = calcIndex(nums2, mid);
            if (idx1 + idx2 > k) {
                r = mid;
            } else {
                l = mid;
            }
        }
        return l;
    }
    
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        auto length = nums1.size() + nums2.size();
        if (length % 2 == 1) {
            return getKth(nums1, nums2, length / 2);
        } else {
            return (getKth(nums1, nums2, length / 2) + getKth(nums1, nums2, length / 2 - 1)) / 2.0;
        }
    }
};

// 56ms, 21.2MB