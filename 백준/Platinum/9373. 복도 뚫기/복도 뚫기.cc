#include <bits/stdc++.h>
using namespace std;

struct Circle {
    int x, y, r;
    Circle()=default;
    explicit Circle(int x, int y, int r): x(x), y(y), r(r) {}

    [[nodiscard]] double dis(const Circle &o) const {
        double d=hypot(x-o.x, y-o.y)-r-o.r;
        if (d<0) return 0;
        return d;
    }
};
struct Edge {
    int u, v;
    double w;
};
struct DSU {
    vector<int> p;
    explicit DSU(int n=0) { init(n); }
    void init(int n) { p.assign(n, -1); }

    int find(int x) { return p[x]<0? x: p[x]=find(p[x]); }
    bool merge(int x, int y) {
        x=find(x), y=find(y);
        if (x==y) return 0;
        if (p[x]>p[y]) swap(x, y);
        p[x]+=p[y];
        p[y]=x;
        return 1;
    }
    int size(int x) { return -p[find(x)]; }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(10);
    int t;
    cin >> t;
    while (t--) {
        int w, n;
        cin >> w >> n;
        vector<Circle> C(n);
        vector<Edge> G;
        DSU dsu(n+2);
        for (int i=0; i<n; i++)
            cin >> C[i].x >> C[i].y >> C[i].r;
        G.push_back({n, n+1, 1.0*w});
        for (int i=0; i<n; i++) {
            G.push_back({n, i, max(0.0, 1.0*C[i].x-C[i].r)});
            G.push_back({n+1, i, max(0.0, 1.0*w-C[i].x-C[i].r)});
            for (int j=i+1; j<n; j++)
                G.push_back({i, j, C[i].dis(C[j])});
        }
        ranges::sort(G, [](auto &a, auto &b) {
            return a.w<b.w;
        });
        auto one=[&]() {
            for (auto &e: G) {
                dsu.merge(e.u, e.v);
                if (dsu.find(n)==dsu.find(n+1)) return e.w/2;
            }
            return 0.0;
        };
        cout << one() << '\n';
    }
}