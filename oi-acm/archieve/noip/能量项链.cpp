#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;  
int num[maxn]; 
int f[maxn][maxn];  
  
int main() {  
    int n;  
    while (scanf("%d", &n) != EOF) {   
        for (int i = 0; i < n; i++) {
            scanf("%d", &num[i]);  
        }
        memset(f, 0, sizeof(f));  
        for (int l = 1; l < n; l++) {
            for (int i = 0; i < n; i++) {  
                int j = (l + i) % n;
                for (int k = i; k != j; k = (k + 1) % n) {  
                    f[i][j] = max(f[i][j], f[i][k] + f[(k + 1) % n][j] 
                        + num[i] * num[(k + 1) % n] * num[(j + 1) % n]); 
                }  
            }  
        }
        int ans = 0;  
        for(int i = 0; i < n; i++) {
            ans = max(ans, f[i][(i - 1 + n) % n]);  
        }
        printf("%d\n", ans);  
    }
    return 0;  
}  