#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

struct Edge {
    int u, v;
    lint w;
};

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m, q;
    cin >> n >> m >> q;
    vector<Edge> E(m);
    vector<vector<pair<int, lint>>> G(n+1);
    for (auto &[u, v, w]: E) {
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }

    vector<int> conn(n+1, -1), stk;
    vector<lint> dis(n+1), cg;
    int c=0;
    for (int s=1; s<=n; s++) {
        if (conn[s]!=-1) continue;
        conn[s]=c;
        dis[s]=0;
        stk.clear();
        stk.emplace_back(s);
        for (int i=0; i<stk.size(); i++)
            for (auto [to, w]: G[stk[i]]) {
                if (conn[to]!=-1) continue;
                conn[to]=c;
                dis[to]=dis[stk[i]]+w;
                stk.emplace_back(to);
            }
        cg.emplace_back(0);
        c++;
    }
    for (auto &[u, v, w]: E) {
        cg[conn[u]]=gcd(cg[conn[u]], llabs(dis[u]+w-dis[v]));
        cg[conn[u]]=gcd(cg[conn[u]], llabs(dis[v]+w-dis[u]));
    }

    while (q--) {
        int a, b;
        lint k;
        cin >> a >> b >> k;
        cout << (
            conn[a]==conn[b] &&
            (dis[b]-dis[a])%gcd(cg[conn[a]], k)==0?
            "Yes": "No"
        ) << '\n';
    }
}