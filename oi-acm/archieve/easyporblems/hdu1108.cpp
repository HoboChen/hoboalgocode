#include <bits/stdc++.h>

using namespace std;

int main() {
    int a, b;
    while (cin >> a >> b) {
        long long t = __gcd(a, b);
        long long ans = (long long)a * b / t;
        cout << ans << endl;
    }

}
