class Solution {
public:

    int dcmp(int x) {
        if (x > 0) return 1;
        if (x < 0) return -1;
        return 0;
    }

    int reverse(int x) {
        int sign = dcmp(x);
        if (sign == 0 || x == -2147483648) return 0;
        x = x / sign;
        vector<int> t;
        while (x) {
            t.push_back(x % 10);
            x /= 10;
        }
        
        for (auto x : t) cout << x;
        cout << endl;
        
        int ret = 0;
        for (auto x : t) {
            if ((2147483647 - x) / 10 < ret) return 0; // this works
            ret *= 10;
            ret += x;
        }
        return ret * sign;
    }
};