#include <bits/stdc++.h>
using namespace std;
constexpr int N=70001;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int t;
    cin >> t;
    vector<pair<int, int>> q(t);
    for (auto &[n, L]: q) cin >> n >> L;

    vector dp(6, vector<int>(N));
    vector pre(N, 0), cur(N, 0), pref(N, 0);
    pre[1]=1;
    for (int i=1; i<N; i++) dp[1][i]=pre[i];
    for (int k=2; k<6; k++) {
        pref[0]=0;
        for (int i=1; i<N; i++) pref[i]=pref[i-1]+pre[i];
        for (int i=1; i<N; i++) {
            int u=sqrt(i-1);
            cur[i]=pref[u];
            dp[k][i]=cur[i];
        }
        pre.swap(cur);
        ranges::fill(cur, 0);
    }
    for (auto [n, L]: q)
        cout << (L>5? 0: dp[L][n]) << '\n';
}