#include <bits/stdc++.h>
using namespace std;

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
    cin.tie(0)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> h(n);
    for (int i=0; i<n; i++) cin >> h[i];
    vector<pair<int, int>> e(m);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        e[i]={u-1,v-1};
    }

    vector<int> vals=h;
    ranges::sort(vals);
    vals.erase(ranges::unique(vals).begin(), vals.end());

    int U=vals.size();
    vector<int> rk(n);
    for (int i=0; i<n; i++)
        rk[i]=ranges::lower_bound(vals, h[i])-vals.begin();

    auto ok=[&](int l, int r)->bool {
        if (!(l<=rk[0] && rk[0]<=r)) return false;
        if (!(l<=rk[1] && rk[1]<=r)) return false;

        DSU dsu(n);
        for (auto [u, v]: e)
            if (l<=rk[u] && rk[u]<=r && l<=rk[v] && rk[v]<=r) dsu.merge(u,v);
        return dsu.find(0)==dsu.find(1);
    };

    int rs=INT_MAX, r=0;
    for (int l=0; l<U; l++) {
        if (r<l) r=l;
        while (r<U && !ok(l, r)) r++;
        if (r==U) break;
        rs=min(rs, vals[r]-vals[l]);
    }
    cout << rs << '\n';
}