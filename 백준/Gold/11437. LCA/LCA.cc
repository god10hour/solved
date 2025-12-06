#include <bits/stdc++.h>
using namespace std;
constexpr int N=50001;
constexpr int LOG=18;

int dp[LOG][N], height[N];
bool vis[N];
vector<int> adj[N];

void dfs(int u) {
    vis[u]=1;
    for (int v: adj[u])
        if (!vis[v]) {
            height[v]=height[u]+1;
            dp[0][v]=u;
            dfs(v);
        }
}

int lca(int u, int v) {
    if (height[u]>height[v]) swap(u, v);
    int d=height[v]-height[u];
    for (int i=0; i<LOG; i++)
        if (d&(1<<i)) v=dp[i][v];
    if (u==v) return u;
    for (int i=LOG-1; i>=0; i--)
        if (dp[i][u]!=dp[i][v]) u=dp[i][u], v=dp[i][v];
    return dp[0][u];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n;
    for (int i=0; i<n-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dp[0][1]=1;
    dfs(1);
    for (int i=1; i<LOG; i++)
        for (int j=1; j<=n; j++)
            dp[i][j]=dp[i-1][dp[i-1][j]];

    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
}