#include "leetcode.h"

class Solution {

private:
    
    long long check(long long base, int len) {
        long long ret = 0, tmp = 1;
        for (int i = 0; i < len; i++) {
            ret += tmp;
            tmp = tmp * base;
        }
        return ret;
    }

    long long isvalid(long long x, int len) {
        long long ret, l = 0, r = (long long)(0x3e3e3e3e) * 0x3e3e3e3e, mid;
        while (l < r - 1) {
            mid = l + (r - l) / 2;
            if (check(mid, len) <= x) {
                ret = l;
                l = mid;
            }
            else r = mid;
        }
        return ret;
    }
    
public:
    string smallestGoodBase(string n) {
        long long ret, x = 0;
        for (int i = 0; i < n.size(); i++) {
            x *= 10;
            x += n[i] - '0';
        }
        for (int i = n.size() - 1; i >= 2; i--) {
            if (isvalid(x, i) != -1) {
                ret = isvalid(x, i);
                return hobo::AnythingToString(ret);
            }
        }
        return "0";
    }
};

int main() {
	
	return 0;
}
