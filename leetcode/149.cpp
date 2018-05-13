#include "leetcode.h"

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
    private:
        int solve(int pos, vector<Point>& points) {
            int ret = 0, zero = 1;
            unordered_map<long long, int> f;
            int px = points[pos].x, py = points[pos].y;
            for (int i = 0; i < points.size(); i++) {
                if (i != pos) {
                    int tx = points[i].x - px, ty = points[i].y - py;
                    if (tx == 0 && ty == 0) { zero++; continue; }
                    else {
                        if (tx == 0) { f[1]++; continue; }
                        if (ty == 0) { f[INT_MAX]++; continue; }
                    }
                    int tmp = __gcd(tx, ty);
                    tx /= tmp, ty /= tmp;
                    if (tx < 0) tx *= -1, ty *= -1;
                    f[(long long)tx * INT_MAX + ty]++;
                }
            }
            for (auto t = f.begin(); t != f.end(); t++)
                ret = max(ret, t -> second);
            return ret + zero;
        }

    public:

        int maxPoints(vector<Point>& points) {
            if (points.size() <= 2) return points.size();
            int ans = 0;
            for (int i = 0; i < points.size(); i++)
                ans = max(ans, solve(i, points));
            return ans;
        }
};
