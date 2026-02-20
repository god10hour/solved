#include <bits/stdc++.h>
using namespace std;
constexpr int mod=1e9+7;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector dp(3, vector(n+1, 0));
    dp[2][1]=1;
    for (int i=2; i<=n; i++) {
        dp[0][i]=(dp[1][i-1]+dp[2][i-1])%mod;
        dp[1][i]=(dp[2][i-1]+dp[0][i-1])%mod;
        dp[2][i]=(dp[0][i-1]+dp[1][i-1])%mod;
    }
    cout << dp[0][n] << '\n';
}