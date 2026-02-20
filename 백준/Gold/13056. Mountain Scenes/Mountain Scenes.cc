#include <bits/stdc++.h>
using namespace std;
constexpr int mod=1e9+7;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, w, h, r=0;
    cin >> n >> w >> h;
    vector dp(w+1, vector(n+1, 0));
    dp[0][0]=1;
    for (int i=1; i<=w; i++)
        for (int j=0; j<=n; j++) if (dp[i-1][j])
            for (int k=0; k<=h; k++) {
                if (j+k>n) break;
                (dp[i][j+k]+=dp[i-1][j])%=mod;
            }
    for (int i=0; i<=n; i++) (r+=dp[w][i])%=mod;
    for (int i=0; i<=h; i++) if (i*w<=n) r--;
    (r+=mod)%=mod;
    cout << r << '\n';
}