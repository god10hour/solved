#include <bits/stdc++.h>
using namespace std;
constexpr int N=100;
array<array<int, N>, N> v, dp;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        v[a][b]=v[b][a]=1;
    }

    for (int i=1; i<N; i++)
        for (int j=i-1; j>=0; j--) {
            dp[j][i]=v[j][i];
            for (int k=j+1; k<i; k++)
                dp[j][i]=max(dp[j][i], v[j][i]+dp[j][k]+dp[k][i]);
        }
    cout << dp[0][N-1] << '\n';
}
