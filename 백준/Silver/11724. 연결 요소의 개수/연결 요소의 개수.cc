#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, s=0;
    cin >> n >> m;
    vector<vector<int>> g(n+1);
    vector<bool> vis(n+1, 0);
    for (int i=0; i<m; i++) {
        int v, u;
        cin >> v >> u;
        g[v].push_back(u);
        g[u].push_back(v);
    }

    function<void(int)> dfs=[&](int u) {
        vis[u]=1;
        for (int v: g[u])
            if (!vis[v])
                dfs(v);
    };
    for (int i=1; i<=n; i++)
        if (!vis[i]) {
            dfs(i);
            s++;
        }
    cout << s;
}
