class LRUCache {
private:
    
    list<pair<int, int>> kv;
    unordered_map<int, list<pair<int, int>>::iterator> kidx;
    int cap;
    
    void update(int key) {
        auto it = kidx[key];
        kv.push_back(*it);
        kv.erase(it);
        kidx[key] = --kv.end();
    }

public:

    LRUCache(int capacity) : cap(capacity) { }

    int get(int key) {
        if (kidx.find(key) != kidx.end()) {
            update(key);
            return kidx[key] -> second;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (kidx.find(key) != kidx.end()) {
            // update
            kidx[key] -> second = value;
            update(key);
        } else {
            // insert
            kv.push_back(make_pair(key, value));
            kidx[key] = --kv.end();
        }
        if (kv.size() > cap) {
            auto it = kv.begin();
            kidx.erase(it -> first);
            kv.erase(it);
        }
    }
};

// 136ms, 40.1MB