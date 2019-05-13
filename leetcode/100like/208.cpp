class Trie {

private:
    
    struct Node {
        Node* next[26];
        int val;
        int cnt;
        
        Node(int val, int cnt = 0) : val(val), cnt(cnt) {
            memset(next, 0, sizeof(next));
        }
    };
    
    Node* root;
    
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new Node(-1);
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Node* current = root;
        for (auto c : word) {
            if (current -> next[c - 'a'] == NULL) {
                current -> next[c - 'a'] = new Node(c - 'a');
            }
            current = current -> next[c - 'a'];
        }
        current -> cnt += 1;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Node* current = root;
        for (auto c : word) {
            if (!current -> next[c - 'a']) {
                return false;
            }
            current = current -> next[c - 'a'];
        }
        return current -> cnt > 0;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Node* current = root;
        for (auto c : prefix) {
            if (!current -> next[c - 'a']) {
                return false;
            }
            current = current -> next[c - 'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */

// 80ms, 44.7MB