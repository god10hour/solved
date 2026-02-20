#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    lint n, m, k;
    cin >> n >> m >> k;
    vector<lint> v(n+1), dp(n+1);
    for (int i=1; i<=n; i++) {
        cin >> v[i];
        dp[i]=i*k;
    }
    for (int i=1; i<=n; i++) {
        lint lmin=v[i], lmax=v[i];
        for (int j=0; j<m; j++) {
            if (i==j) break;
            lmin=min(lmin, v[i-j]);
            lmax=max(lmax, v[i-j]);
            dp[i]=min(dp[i], k+(j+1)*(lmax-lmin)+dp[i-j-1]);
        }
    }
    cout << dp[n] << '\n';
}