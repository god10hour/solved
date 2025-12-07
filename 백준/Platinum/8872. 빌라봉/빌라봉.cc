#include <bits/stdc++.h>
using namespace std;
constexpr int N=100001;
constexpr int inf=1e9;
vector<pair<int, int>> adj[N];
int vis[N], dis[N], par[N], c=1;

int dfs(int u) {
    vis[u]=c;
    int r=u;
    dis[u]=0;
    for (auto [from, w]: adj[u]) {
        if (vis[from]==c) continue;
        int child=dfs(from);
        if (dis[from]+w>dis[u]) {
            dis[u]=dis[from]+w;
            r=child;
            par[from]=u;
        }
    }
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, l;
    cin >> n >> m >> l;
    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    int diam=0;
    vector<int> rad;
    for (int i=0; i<n; i++) {
        if (vis[i]) continue;
        int x=dfs(i);
        c++, par[x]=-1;
        int y=dfs(x), d=dis[x], r=inf;

        while (y!=-1) {
            int k=max(d-dis[y], dis[y]);
            r=min(r, k);
            y=par[y];
        }
        rad.emplace_back(r);
        diam=max(diam, d);
    }
    ranges::sort(rad, greater<>());
    int s=diam;
    if (rad.size()>1) s=max(s, rad[0]+rad[1]+l);
    if (rad.size()>2) s=max(s, rad[1]+rad[2]+l*2);
    cout << s << '\n';
}