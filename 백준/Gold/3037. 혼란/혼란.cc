#include <bits/stdc++.h>
using namespace std;
constexpr int mod=1e9+7;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, c;
    cin >> n >> c;
    vector dp(n+1, vector(c+1, 0));
    dp[1][0]=1;
    for (int i=2; i<=n; i++) {
        int s=0;
        for (int j=0; j<=c; j++) {
            s+=dp[i-1][j];
            if (i<=j) s-=dp[i-1][j-i];
            if (s<0) s+=mod;
            if (s>=mod) s-=mod;
            dp[i][j]=s;
        }
    }
    cout << dp[n][c] << '\n';
}