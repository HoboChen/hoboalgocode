class Solution {
public:
    int numJewelsInStones(string J, string S) {
        unordered_multiset<char> stones;
        int ans = 0;
        for (const auto x : S) {
            stones.insert(x);
        }
        for (const auto x : J) {
            ans += stones.count(x);
        }
        return ans;
    }
};

// 8ms, 10.2MB