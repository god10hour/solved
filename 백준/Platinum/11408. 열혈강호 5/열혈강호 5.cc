#include <bits/stdc++.h>
using namespace std;

class MCMF {
public:
    static constexpr int     INF_CAP =1e9;
    static constexpr int64_t INF_COST=1LL<<60;
    static constexpr int64_t INF_FLOW=1LL<<60;

    explicit MCMF(int n)
        : N(n), g(n), pi(n, 0), dist(n), pv_v(n), pv_e(n) {}

    void add(int u, int v, int cap, int cost) {
        Edge a(v, (int)g[v].size(), cap, cost);
        Edge b(u, (int)g[u].size(), 0, -cost);
        g[u].push_back(a);
        g[v].push_back(b);
    }

    pair<int64_t, int64_t> get(int S, int T, int64_t K=INF_FLOW) {
        spfa_init(S);

        int64_t flow=0, cost=0;
        while (flow<K && dijkstra(S, T)) {
            for (int i=0;i<N;i++) if (dist[i]<INF_COST) pi[i]+=dist[i];

            int aug=INF_CAP;
            for (int v=T; v!=S; v=pv_v[v]) {
                auto &e=g[pv_v[v]][pv_e[v]];
                aug=min(aug, e.cap);
            }
            if (K!=INF_FLOW) aug=min<int64_t>(aug, K-flow);

            for (int v=T; v!=S; v=pv_v[v]) {
                auto &e =g[pv_v[v]][pv_e[v]];
                auto &re=g[v][e.rev];
                e.cap-=aug;
                re.cap+=aug;
                cost+=1LL*aug*e.cost;
            }
            flow+=aug;
        }
        return {flow, cost};
    }

private:
    struct Edge {
        int to, rev, cap, cost;
        Edge(int to,int rev,int cap,int cost):to(to),rev(rev),cap(cap),cost(cost){}
    };

    int N;
    vector<vector<Edge>> g;
    vector<int64_t> pi, dist;
    vector<int> pv_v, pv_e;

    void spfa_init(int S) {
        fill(pi.begin(), pi.end(), 0);
    }

    bool dijkstra(int S, int T) {
        dist.assign(N, INF_COST);
        pv_v.assign(N, -1);
        pv_e.assign(N, -1);

        using P = pair<int64_t,int>;
        priority_queue<P, vector<P>, greater<P>> pq;
        dist[S]=0; pq.push({0,S});

        while (!pq.empty()) {
            auto [d,u]=pq.top(); pq.pop();
            if (d!=dist[u]) continue;
            for (int i=0; i<g[u].size(); i++) {
                auto &e=g[u][i];
                if (e.cap<=0) continue;
                int64_t need=d+1LL*e.cost+pi[u]-pi[e.to];
                if (need<dist[e.to]) {
                    dist[e.to]=need;
                    pv_v[e.to]=u;
                    pv_e[e.to]=i;
                    pq.push({need, e.to});
                }
            }
        }
        return pv_v[T]!=-1;
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, k;
    cin >> n >> m;

    const int S=0;
    const int T=n+m+1;
    MCMF mcmf(T+1);

    for (int i=1; i<=n; i++)
        mcmf.add(S, i, 1, 0);
    for (int i=1; i<=m; i++)
        mcmf.add(n+i, T, 1, 0);
    for (int i=1; i<=n; i++) {
        cin >> k;
        while (k--) {
            int job, wage;
            cin >> job >> wage;
            mcmf.add(i, n+job, 1, wage);
        }
    }
    auto [flow, cost]=mcmf.get(S, T);
    cout << flow << '\n' << cost << '\n';
}