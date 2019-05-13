class LRUCache {
    
    map<int, int> kv;
    map<int, int> keyOperation; // key -> lastOperation
    map<int, int> operationKey; // lastOperation -> key
    int capacity;
    int operation;


    // not the update of LRU
    void update(int key, int operation) {
        if (keyOperation.find(key) != keyOperation.end()) {
            int formerOperation = keyOperation[key];
            operationKey.erase(formerOperation);
        }
        keyOperation[key] = operation;
        operationKey[operation] = key;
    }

public:
    LRUCache(int capacity) : capacity(capacity), operation(0) { }
    
    int get(int key) {
        operation++;
        if (kv.find(key) != kv.end()) {
            update(key, operation);
            return kv[key];
        }
        return -1;
    }
    
    void put(int key, int value) {
        operation++;
        kv[key] = value;
        update(key, operation);
        if (kv.size() > capacity) {
            auto oldest = operationKey.begin();
            int operationToDelete = oldest -> first;
            int keyToDelete = oldest -> second;    
            kv.erase(keyToDelete);
            keyOperation.erase(keyToDelete);
            operationKey.erase(operationToDelete);
        }
    }
};

// 164ms, 41.9MB