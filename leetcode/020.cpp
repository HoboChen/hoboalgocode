class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (auto x : s) {
            if (x == '(' || x == '{' || x == '[')
                st.push(x);
            else
                if (x == ')')
                    if (st.size() && st.top() == '(') st.pop();
                    else return 0;
                else if (x == ']')
                    if (st.size() && st.top() == '[') st.pop();
                    else return 0;
                else if (x == '}')
                    if (st.size() && st.top() == '{') st.pop();
                    else return 0;
        }
        return st.empty();
    }
};