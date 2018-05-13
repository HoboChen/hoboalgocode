#include <bits/stdc++.h>

using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};


class Solution {

private:
    inline bool notIntersect(Interval a, Interval b) {
        return a.end < b.start || a.start > b.end;
    }

public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> ret;
        for (unsigned i = 0; i < intervals.size(); i++) {
            if (notIntersect(intervals[i], newInterval)) ret.push_back(intervals[i]);
        }
        return ret;
    }

};
