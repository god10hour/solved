#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k, x, a[4];
    vector<int> adj[4];
    cin >> n >> k;
    vector<pair<int, int>> v(n);
    for (int i=0; i<4; i++) cin >> a[i];
    for (int i=0; i<n; i++) {
        char r;
        cin >> r >> x;
        adj[r-65].push_back(x);
    }
    for (int i=0; i<4; i++) sort(adj[i].begin(), adj[i].end());
    for (int i=0; i<k; i++) {
        int idx;
        bool b[4];
        for (int j=0; j<4; j++) b[j]=!adj[j].empty();
        for (int j=0; j<4; j++)
            for (int l=j+1; l<4; l++)
                if (!adj[j].empty() && !adj[l].empty()) {
                    int p=adj[j].back(), q=adj[l].back();
                    p*=a[l],q*=a[j];
                    if (p>q)
                        b[l]=0;
                    else b[j]=0;
                }
        for (int j=0; j<4; j++) if (b[j]) idx=j;
        a[idx]+=adj[idx].back();
        v[i]={idx, adj[idx].back()};
        adj[idx].pop_back();
    }
    for (int i=0; i<k; i++)
        cout << "ABCD"[v[i].first] << ' ' << v[i].second << '\n';
}