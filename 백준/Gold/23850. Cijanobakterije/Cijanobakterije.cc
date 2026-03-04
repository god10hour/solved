#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

pair<int, int> bfs(int s, const vector<vector<int>> &adj, vector<int> &dist) {
    queue<int> q;
    dist[s]=0;
    q.push(s);
    int far=s, dis=0;

    while (!q.empty()) {
        int u=q.front();
        q.pop();
        if (dist[u]>dis) dis=dist[u], far=u;
        for (int v: adj[u]) if (dist[v]==-1) {
            dist[v]=dist[u]+1;
            q.push(v);
        }
    }
    return {far, dis};
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n+1);
    while (m--) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> dist(n+1, -1);
    vector<bool> vis(n+1, 0);

    lint s=0, c=0;
    for (int i=1; i<=n; i++) if (!vis[i]) {
        queue<int> q;
        vector<int> nodes;
        dist[i]=0;
        vis[i]=1;
        q.push(i);
        nodes.push_back(i);

        int far=i, r=0;
        while (!q.empty()) {
            int u=q.front();
            q.pop();
            if (dist[u]>r) r=dist[u], far=u;
            for (int v: adj[u]) if (!vis[v]) {
                vis[v]=1;
                dist[v]=dist[u]+1;
                q.push(v);
                nodes.push_back(v);
            }
        }

        for (int x: nodes) dist[x]=-1;
        auto [f, d]=bfs(far, adj, dist);
        (void)f;
        for (int x: nodes) dist[x]=-1;
        s+=d, c++;
    }
    cout << (s+c) << '\n';
    return 0;
}