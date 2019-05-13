#include "leetcode.h"

class LRUCache{
    private:
        map<int, int> LRU;
        map<int, int> frq;
        map<int, int> frqrev;
        int cap;
        int op;
    public:
        LRUCache(int capacity) {
            cap = capacity;
            op = 0;
        }

        int get(int key) {
            op++;
            if (LRU.find(key) != LRU.end()) {
                frq[key] = op;
                return LRU[key];
            }
            return -1;
        }

        void set(int key, int value) {
            op++;
            LRU[key] = value;
            frp[key] = op;
            if (LRU.size() == cap) {
                auto t =
            }
        }
};
