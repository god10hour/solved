#include <bits/stdc++.h>
using namespace std;

// Bipartite Matching: O(√V*E)
struct HopcroftKarp {
    int Ln, Rn;
    vector<vector<int>> g;
    vector<int> dist;
    vector<int> Lmatch, Rmatch;

    explicit HopcroftKarp(int Ln, int Rn): Ln(Ln), Rn(Rn), g(Ln) {
        dist.resize(Ln);
        Lmatch.assign(Ln, -1);
        Rmatch.assign(Rn, -1);
    }

    void add(int u, int v) {
        g[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        bool reachable=false;

        for (int u=0; u<Ln; u++)
            if (Lmatch[u]==-1)
                dist[u]=0, q.push(u);
            else dist[u]=-1;
        while (!q.empty()) {
            int u=q.front(); q.pop();
            for (int v: g[u]) {
                int u2=Rmatch[v];
                if (u2!=-1 && dist[u2]==-1) {
                    dist[u2]=dist[u]+1;
                    q.push(u2);
                }
                if (u2==-1)
                    reachable=true;
            }
        }
        return reachable;
    }

    bool dfs(int u) {
        for (int v: g[u]) {
            int u2=Rmatch[v];
            if (u2==-1 || (dist[u2]==dist[u]+1 && dfs(u2))) {
                Lmatch[u]=v;
                Rmatch[v]=u;
                return true;
            }
        }
        dist[u]=-1;
        return false;
    }

    int max() {
        int m=0;
        while (bfs())
            for (int u=0; u<Ln; u++)
                if (Lmatch[u]==-1 && dfs(u))
                    m++;
        return m;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        HopcroftKarp BM(n, n);
        while (m--) {
            int u, v;
            cin >> u >> v;
            BM.add(u, v);
        }
        cout << BM.max() << '\n';
    }
}