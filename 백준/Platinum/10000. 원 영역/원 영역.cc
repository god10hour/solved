#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    explicit DSU(int n=0) { init(n); }
    void init(int n) { p.assign(n, -1); }

    int find(int x) { return p[x]<0? x: p[x]=find(p[x]); }
    bool join(int x, int y) {
        x=find(x), y=find(y);
        if (x==y) return 0;
        if (p[x]>p[y]) swap(x, y);
        p[x]+=p[y];
        p[y]=x;
        return 1;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> L(n), R(n), v(n*2);
    for (int i=0; i<n; i++) {
        int x, r;
        cin >> x >> r;
        L[i]=x-r, R[i]=x+r;
        v[i*2]=L[i], v[i*2+1]=R[i];
    }
    ranges::sort(v);
    v.erase(ranges::unique(v).begin(), v.end());

    int V=v.size(), E=n*2, C=0;
    DSU dsu(V);
    for (int i=0; i<n; i++) {
        int l=ranges::lower_bound(v, L[i])-v.begin(), r=ranges::lower_bound(v, R[i])-v.begin();
        dsu.join(l, r);
    }
    for (int i=0; i<V; i++) if (i==dsu.find(i)) C++;
    cout << 1-V+E+C << '\n';
}