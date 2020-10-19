#include <bits/stdc++.h>

using namespace std;

const int N = 99999;

struct Trie {
private:

    struct Node {
        int value;
        Node* child[10];

        Node(int val) {
            value = val;
            for (int i = 0; i < 10; i++) {
                child[i] = 0;
            }
        }
    };

public:

    Trie() {
        root = new Node(-1);
    }

    void insert(string c, int value) {
        insert(root, c, 0, value);
        
    }

    int find(string c) {
        return find(root, c, 0);
    }

private:

    void insert(Node* cur, string c, int idx, int value) {
        if (idx >= c.length()) {
            return;
        }
        if (!cur -> child[c[idx] - '0']) {
            cur -> child[c[idx] - '0'] = new Node(value);
        }
        insert(cur -> child[c[idx] - '0'], c, idx + 1, value);
    }

    int find(Node* cur, string c, int idx) {
        if (!cur) {
            return -1;
        }
        if (idx == c.length()) {
            return cur -> value;
        }
        return find(cur -> child[c[idx] - '0'], c, idx + 1);
    }

    Node* root;
};

int main() {
    Trie trie;

    string f0 = "1";
    string f1 = "1";
    trie.insert(f0, 0);
    trie.insert(f1, 1);

    // calculate fib and insert to trie
    for (int i = 0; i < N - 1; i++) {
        string c;
        // c.reserve(f1.length()); 
        int carry = 0;
        for (int j = 0; j < max(f0.length(), f1.length()); j++) {
            int digit = 0;
            if (j < f0.length()) {
                digit += f0[j] - '0';
            }
            if (j < f1.length()) {
                digit += f1[j] - '0';
            }
            digit += carry;
            carry = digit / 10;
            digit %= 10;
            c.push_back((char)digit + '0');
        }
        if (carry) {
            c.push_back((char)carry + '0');
        }
        string d = "";
        for (int j = c.length() - 1; j >= 0; j--) {
            d.push_back(c[j]);
            if (d.length() >= 100) {
                break;
            }
        }
        // reverse(c.begin(), c.end());
        // string d = c.substr(0, min(c.length(), (size_t)100));
        // reverse(c.begin(), c.end());
        f0 = f1;
        f1 = c;
        trie.insert(d, i + 2);
    }

    // deal with the issue
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string x;
        cin >> x;
        printf("Case #%d: %d\n", i + 1, trie.find(x));
    }
}
