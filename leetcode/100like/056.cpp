/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
private:
    
    static int cmp(const Interval& a, const Interval& b) {
        return a.start < b.start;
    }
    
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        vector<Interval> ans;
        for (const auto interval : intervals) {
            if (ans.empty()) {
                ans.push_back(interval);
                continue;
            }
            if (interval.start <= ans.back().end) {
                ans.back().end = max(ans.back().end, interval.end);
            } else {
                ans.push_back(interval);
            }
        }
        return ans;
    }
};

// 12ms, 9.9MB