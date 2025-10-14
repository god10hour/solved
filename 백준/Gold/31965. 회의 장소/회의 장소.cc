#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int> v(n+1), pre(n+1, 0);
    for (int i=1; i<=n; i++) {
        cin >> v[i];
        pre[i]=pre[i-1]+v[i];
    }

    auto cost=[&](int i, int j, int k) {
        int l=(k-i+1)*v[k]-(pre[k]-pre[i-1]);
        int r=(pre[j]-pre[k-1])-(j-k+1)*v[k];
        return l+r;
    };
    while (q--) {
        int a, b;
        cin >> a >> b;
        int L=lower_bound(v.begin()+1, v.end(), a)-v.begin();
        int U=upper_bound(v.begin()+1, v.end(), b)-v.begin()-1;
        if (L<U)
            cout << max(cost(L, U, L), cost(L, U, U))-cost(L, U, (L+U)/2);
        else cout << 0;
        cout << '\n';
    }
}