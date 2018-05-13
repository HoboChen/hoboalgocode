/* #include "leetcode.h" */

class Solution {
    vector<string> digit2eng = {
        "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen",
        "fifteen", "sixteen", "seventeen", "eighteen", "nineteen", // 0 - 19
        "twenty", "thirty", "forty", "fifty", "sixty",
        "seventy", "eighty", "ninety",
    };
    vector<string> j2eng = {"Hundred", "Thousand", "Million", "Billion"};

    private:
    string atomic(int x) {
        string t = digit2eng[x];
        t[0] = toupper(t[0]);
        return t + " ";
    }

    string smaller(int x) { // x < 1000
        string t = "";
        if (x >= 100) {
            t += atomic(x / 100);
            t += j2eng[0] + " ";
            x %= 100;
            if (x == 0) return t;
        }
        if (x <= 20) { t += atomic(x); return t; }
        t += atomic(x / 10 + 18);
        x %= 10;
        if (x == 0) return t;
        return t + atomic(x);
    }

    public:
    string hobonumberToWords(int num) {
        string ret;
        int E9 = (int)(1e9 + 0.5), E6 = (int)(1e6 + 0.5), E3 = (int)(1e3 + 0.5);
        if (num >= E9) {
            ret += smaller(num / E9);
            ret += j2eng[3] + " ";
            num %= E9;
            if (num == 0) return ret;
        }
        if (num >= E6) {
            ret += smaller(num / E6);
            ret += j2eng[2] + " ";
            num %= E6;
            if (num == 0) return ret;
        }
        if (num >= E3) {
            ret += smaller(num / E3);
            ret += j2eng[1] + " ";
            num %= E3;
            if (num == 0) return ret;
        }
        ret += smaller(num);
        return ret;
    }

    string numberToWords(int num) {
        string ret;
        ret = hobonumberToWords(num);
        ret = ret.substr(0, ret.size() - 1);
        return ret;
    }
};

/* int main() { */
/*     Solution s; */
/*     int t; */
/*     while (cin >> t) { */
/*         cout << s.numberToWords(t) << endl; */
/*     } */
/*     return 0; */
/* } */
