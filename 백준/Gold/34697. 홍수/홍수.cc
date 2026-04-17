#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m;
    vector<int> h(n+1);
    vector vis(n+1, false);
    vector<vector<int>> adj(n+1);
    queue<int> q;

    for (int i=1; i<=n; i++) cin >> h[i];
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        if (h[u]<h[v])
            adj[u].push_back(v);
        else adj[v].push_back(u);
    }
    cin >> k;
    vector<int> a(k);
    for (int i=0; i<k; i++) {
        cin >> a[i];
        vis[a[i]]=1;
        q.push(a[i]);
    }
    while (!q.empty()) {
        int u=q.front();
        q.pop();
        for (int v: adj[u]) {
            if (vis[v]) continue;
            vis[v]=true;
            q.push(v);
        }
    }

    for (int i=1; i<=n; i++) if (!vis[i])
        return !(cout << "flood\n");
    cout << "no flood\n";
}