#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

struct edge {
    lint v, w;
    bool operator<(const edge &o) const {
        return w>o.w;
    }
};
lint dis[22][10001];
vector<edge> adj[10001];

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    memset(dis, 0x7F, sizeof dis);
    dis[0][1]=0;

    for (int i=0; i<=k; i++) {
        priority_queue<edge> q;
        for (int j=1; j<=n; j++) q.push({j, dis[i][j]});
        while (!q.empty()) {
            auto [v, w]=q.top();
            q.pop();
            if (w>dis[i][v]) continue;

            for (auto e: adj[v])
                if (dis[i][e.v]>w+e.w) {
                    dis[i][e.v]=w+e.w;
                    q.push({e.v, w+e.w});
                }
        }
        memcpy(dis[i+1], dis[i], sizeof dis[i]);
        for (int j=1; j<=n; j++)
            for (auto [v, w]: adj[j])
                dis[i+1][v]=min(dis[i+1][v], dis[i][j]);
    }
    cout << dis[k][n] << '\n';
}