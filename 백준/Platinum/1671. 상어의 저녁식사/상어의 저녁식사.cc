#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

class Dinic {
public:
    static constexpr lint inf=1e18;
    explicit Dinic(size_t size, int source, int sink):
        source(source), sink(sink), adj(size), cur(size), level(size) {};
    ~Dinic()=default;

    void add(int from, int to, lint wei) {
        pool.emplace_back(make_unique<Edge>(to, wei));
        pool.emplace_back(make_unique<Edge>(from, 0));
        auto *e=pool[pool.size()-2].get();
        auto *rev=pool[pool.size()-1].get();
        e->rev=rev; rev->rev=e;
        adj[from].push_back(e);
        adj[to].push_back(rev);
    }

    lint get() {
        lint maxflow=0;
        while (build()) {
            ranges::fill(cur, 0);
            lint f;
            while ((f=push(source, inf))) maxflow+=f;
        }
        return maxflow;
    }

private:
    struct Edge {
        Edge *rev=nullptr;
        int to;
        lint cap, flow;
        explicit Edge(int to, lint cap): to(to), cap(cap), flow(0) {}

        void push(lint v) {
            flow+=v;
            rev->flow-=v;
        }

        lint r_capacity() const { return cap-flow; }
    };
    int source=0, sink=0;
    vector<vector<Edge*>> adj;
    vector<unique_ptr<Edge>> pool;
    vector<int> cur, level;

    bool build() {
        ranges::fill(level, -1);
        level[source]=0;
        queue<int> q;
        q.push(source);

        while (!q.empty()) {
            const int u=q.front(); q.pop();

            for (const Edge *e: adj[u]) {
                if (level[e->to]!=-1 || e->r_capacity()==0)
                    continue;
                level[e->to]=level[u]+1;
                q.push(e->to);
            }
        }
        return level[sink]!=-1;
    }

    lint push(int u, lint flow) {
        if (u==sink) return flow;
        for (int &i=cur[u]; i<adj[u].size(); i++) {
            Edge *e=adj[u][i];
            if (level[e->to]!=level[u]+1 || e->r_capacity()==0) continue;
            if (lint f=push(e->to, min(flow, e->r_capacity()))) {
                e->push(f);
                return f;
            }
        }
        return 0;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    Dinic dinic((n+1)*2, 0, n*2+1);
    for (int i=1;   i<=n;   i++) dinic.add(0, i, 2);
    for (int i=n+1; i<=n*2; i++) dinic.add(i, n*2+1, 1);
    vector<array<int, 3>> v(n);
    for (auto &a: v) for (int &i: a) cin >> i;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++) if (i!=j) {
            if (v[i]==v[j]) {
                if (i<j) dinic.add(j+1, n+i+1, 1);
            } else if (
                ranges::all_of(views::iota(0, 3), [&](int k) {
                    return v[i][k]<=v[j][k];
                })
            ) dinic.add(j+1, n+i+1, 1);
        }
    cout << n-dinic.get() << '\n';
}