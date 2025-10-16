#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const int MOD=1e9+7;
int dp[101][101][101];

int f(int n, int l, int r) {
    if (l+r>n+1 || l<1 || r<1 || n<1) return 0;
    if (dp[n][l][r]!=-1) return dp[n][l][r];
    if (dp[n-1][l][r]==-1) dp[n-1][l][r]=f(n-1, l, r);
    if (dp[n-1][l-1][r]==-1) dp[n-1][l-1][r]=f(n-1, l-1, r);
    if (dp[n-1][l][r-1]==-1) dp[n-1][l][r-1]=f(n-1, l, r-1);
    return dp[n][l][r]=(dp[n-1][l-1][r]+dp[n-1][l][r-1]+(n-2)*dp[n-1][l][r])%MOD;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, l, r;
    cin >> n >> l >> r;
    memset(dp, -1, sizeof dp);
    dp[1][1][1]=1;
    cout << f(n, l, r);
}