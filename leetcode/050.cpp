class Solution {
private:
public:
    double myPow(double x, long long n) {
        if (n < 0) return myPow(1.0 / x, -n);
        if (n == 0) return 1.0;
        if (n == 1) return x;
        double t = myPow(x, n / 2);
        if (n & 1)
            return t * t * x;
        return t * t;
    }
};