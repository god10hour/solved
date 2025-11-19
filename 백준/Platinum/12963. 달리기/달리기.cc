#include <bits/stdc++.h>
using namespace std;
constexpr int mod=1e9+7;

struct DSU {
    vector<int> p;
    explicit DSU(int n=0) { init(n); }
    void init(int n) { p.assign(n, -1); }

    int find(int x) { return p[x]<0? x:p[x]=find(p[x]); }
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
    int n, m, r=0;
    cin >> n >> m;
    DSU dsu(n+1);
    vector<int> a(m), b(m), pw(m, 1);
    for (int i=0; i<m; i++) cin >> a[i] >> b[i];
    for (int i=1; i<m; i++) pw[i]=pw[i-1]*3LL%mod;

    for (int i=m-1; i>=0; i--) {
        int A=dsu.find(a[i]), B=dsu.find(b[i]);
        int X=dsu.find(0), Y=dsu.find(n-1);

        if (min(A, B)==min(X, Y) && max(A, B)==max(X, Y))
            r=(r+pw[i])%mod;
        else dsu.merge(A, B);
    }
    cout << r << '\n';
}