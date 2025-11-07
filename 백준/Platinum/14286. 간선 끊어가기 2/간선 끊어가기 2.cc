#include <bits/stdc++.h>
using namespace std;

class Network {
public:
    static constexpr int INF=1e9;
    explicit Network(size_t size, int source, int sink)
        : source(source), sink(sink), adj(size), cur(size), level(size) {};
    ~Network() {
        for (auto p : pool) delete p;
    }

    void add(int from, int to, int wei) {
        Edge *e=new Edge(to, wei);
        Edge *rev=new Edge(from, 0);
        pool.push_back(e);
        pool.push_back(rev);
        e->rev=rev, rev->rev=e;
        adj[from].push_back(e);
        adj[to].push_back(rev);
    }

    int get() {
        int maxflow=0;
        while (build()) {
            fill(cur.begin(), cur.end(), 0);
            int f;
            while ((f=push(source, INF)))
                maxflow+=f;
        }
        return maxflow;
    }

private:
    struct Edge {
        Edge *rev=nullptr;
        int to, cap, flow;
        explicit Edge(int to, int cap): to(to), cap(cap), flow(0) {}

        void push(int v) {
            flow+=v;
            rev->flow-=v;
        }

        int r_capacity() const { return cap-flow; }
    };
    int source=0, sink=0;
    vector<vector<Edge*>> adj;
    vector<Edge*> pool;
    vector<int> cur, level;

    bool build() {
        fill(level.begin(), level.end(), -1);
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

    int push(int u, int flow) {
        if (u==sink) return flow;
        for (int &i=cur[u]; i<adj[u].size(); i++) {
            Edge *e=adj[u][i];

            if (level[e->to]!=level[u]+1 || e->r_capacity()==0)
                continue;
            if (int f=push(e->to, min(flow, e->r_capacity()))) {
                e->push(f);
                return f;
            }
        }
        return 0;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, s, t;
    cin >> n >> m;
    vector<tuple<int, int, int>> edges(m);
    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i]={u-1, v-1, w};
    }
    cin >> s >> t;
    Network network(n, s-1, t-1);
    for (int i=0; i<m; i++) {
        auto [u, v, w]=edges[i];
        network.add(u, v, w);
        network.add(v, u, w);
    }
    cout << network.get() << '\n';
}