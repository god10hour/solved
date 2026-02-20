#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
array<string, 4> base={"", "X", "YZ", "ZX"};
array<lint, 101> dp={0, 1, 2, 2};
array<array<lint, 3>, 101> cnt;

char run(lint idx, int d) {
    if (d<4) return base[d][idx-1];
    if (idx<=dp[d-3]) return run(idx, d-3);
    return run(idx-dp[d-3], d-2);
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int t, n;
    cin >> t >> n;
    cnt[1][0]=1;
    cnt[2][1]=cnt[2][2]=1;
    cnt[3][0]=cnt[3][2]=1;
    for (int i=4; i<=n; i++) {
        dp[i]=dp[i-3]+dp[i-2];
        for (int j=0; j<3; j++)
            cnt[i][j]=cnt[i-3][j]+cnt[i-2][j];
    }

    if (t==1)
        cout << dp[n] << '\n';
    else if (t==2) {
        lint k;
        cin >> k;
        cout << run(k, n) << '\n';
    }
    else {
        char c;
        cin >> c;
        cout << cnt[n][c-'X'] << '\n';
    }
}