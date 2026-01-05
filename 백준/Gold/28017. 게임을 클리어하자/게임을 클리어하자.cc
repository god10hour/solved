#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector v(n, vector<int>(m));
    vector dp(n+1, vector(m+1, 0));
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            cin >> v[i][j];

    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++) {
            int last=1e9+7;
            for (int k=1; k<=m; k++) if (j!=k)
                last=min(last, dp[i-1][k]);
            dp[i][j]=last+v[i-1][j-1];
        }
    int r=dp[n][1];
    for (int i=2; i<=m; i++) r=min(r, dp[n][i]);
    cout << r << '\n';
}