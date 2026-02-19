#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

class NetworkFlow {
public:
    static constexpr lint inf=1e18;
    explicit NetworkFlow(size_t size, int source, int sink)
        : source(source), sink(sink), adj(size), cur(size), level(size) {};
    ~NetworkFlow()=default;

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

template <typename Type>
struct Poi {
    Type x, y;
    Poi()=default;
    explicit Poi(Type x, Type y): x(x), y(y) {}

    Poi operator+(const Poi &p) const { return Poi(x+p.x, y+p.y); }
    Poi operator-(const Poi &p) const { return Poi(x-p.x, y-p.y); }
    Poi operator*(Type k)       const { return Poi(x*k, y*k); }
    friend Poi operator*(Type k, const Poi &p) { return Poi(p.x*k, p.y*k); }

    Type operator*(const Poi &p) const { return x*p.x + y*p.y; }
    Type operator/(const Poi &p) const { return x*p.y - y*p.x; }

    bool operator==(const Poi &p) const { return x==p.x && y==p.y; }
    bool operator< (const Poi &p) const { return x<p.x || (x==p.x && y<p.y); }
    bool operator> (const Poi &p) const { return x>p.x || (x==p.x && y>p.y); }

    static int ccw(const Poi &a, const Poi &b, const Poi &c) {
        Type d=a.x*b.y + b.x*c.y + c.x*a.y - a.x*c.y - b.x*a.y - c.x*b.y;
        return (d>0)-(d<0);
    }
};

template <typename Type>
struct Line {
    using Point=Poi<Type>;
    Point a, b;
    Line()=default;
    explicit Line(auto a, auto b): a(a), b(b) {}

    [[nodiscard]] int lieon(Point x) const { // 0:NO 1:YES, in_between 2:YES, at_end_point
        if (Point::ccw(a, b, x)) return 0;
        if (a==x || b==x) return 2;
        return min(a.x,b.x)<=x.x && x.x<=max(a.x,b.x) &&
               min(a.y,b.y)<=x.y && x.y<=max(a.y,b.y);
    }
    static int intersect(Line L, Line M) {
        // 0: Not intersect
        // 1: Intersect at exactly one point
        // 2: Equal Line, intersect at inf
        auto &[A, B]=L;
        auto &[C, D]=M;
        int c1=Point::ccw(A, B, C), c2=Point::ccw(A, B, D);
        int c3=Point::ccw(C, D, A), c4=Point::ccw(C, D, B);
        if (!c1 && !c2 && !c3 && !c4) {
            if (
                L.lieon(C)==1 || L.lieon(D)==1 ||
                M.lieon(A)==1 || M.lieon(B)==1
            ) return 2;
            if (A==C || B==C) return 2-((D-A)*(D-A)<(D-B)*(D-B));
            if (A==D || B==D) return 2-((C-A)*(C-A)<(C-B)*(C-B));
            return 0;
        }
        return c1!=c2 && c3!=c4;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, k, h, m;
    cin >> n >> k >> h >> m;
    vector<Poi<lint>> wall(n), hole(h), mice(m);
    for (auto &[x, y]: wall) cin >> x >> y;
    for (auto &[x, y]: hole) cin >> x >> y;
    for (auto &[x, y]: mice) cin >> x >> y;

    wall.push_back(wall[0]);
    NetworkFlow dinic(m+h+2, 0, m+h+1);
    for (int i=1; i<=m; i++) dinic.add(0, i, 1);
    for (int i=m+1; i<=m+h; i++) dinic.add(i, m+h+1, k);
    for (int i=0; i<m; i++) for (int j=0; j<h; j++) {
        bool z=true;
        for (int l=0; l<n; l++) {
            Line<lint> L(wall[l], wall[l+1]);
            Line<lint> M(hole[j], mice[i]);
            if (L.lieon(M.a)) continue;
            if (Line<lint>::intersect(L, M)) {
                z=false;
                break;
            }
        }
        if (z) dinic.add(i+1, 1+m+j, 1);
    }
    cout << (m==dinic.get()? "Possible": "Impossible") << '\n';
}