#include <bits/stdc++.h>
using namespace std;
array<array<int, 300000>, 20> dp;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, q;
    cin >> n;
    vector<pair<int, int>> v(n);
    vector<int> u(n*2);
    for (int i=0; i<n; i++) {
        int l, r;
        cin >> l >> r;
        v[i]={l, r};
        u[i*2]=l, u[i*2+1]=r;
    }
    ranges::sort(u);
    u.erase(ranges::unique(u).begin(), u.end());
    for (int i=0; i<n; i++)
        v[i]={
            ranges::lower_bound(u, v[i].first)-u.begin(),
            ranges::lower_bound(u, v[i].second)-u.begin()
        };
    auto vst=v;
    ranges::sort(vst);
    int mx=0;
    for (int i=0, j=0; i<u.size(); i++) {
        while (j<vst.size() && i==vst[j].first)
            mx=max(mx, vst[j++].second);
        dp[0][i]=mx;
    }
    for (int i=1; i<20; i++) for (int j=0; j<u.size(); j++)
        dp[i][j]=dp[i-1][dp[i-1][j]];

    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        auto [xa, xb]=v[x];
        auto [ya, yb]=v[y];
        if ((ya<=xa && xa<=yb) ||
            (ya<=xb && xb<=yb) ||
            (xa<=ya && ya<=xb)) {
            cout << "1\n";
            continue;
        }
        if (xa>ya) swap(xa, ya), swap(xb, yb);
        int t=xb, r=2;
        for (int i=19; i>=0; i--) if (dp[i][t]<ya) {
            t=dp[i][t];
            r+=1<<i;
        }
        cout << (r>n? -1: r) << '\n';
    }
}