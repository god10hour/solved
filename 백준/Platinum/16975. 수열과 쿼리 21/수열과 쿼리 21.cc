#include <bits/stdc++.h>
#define int int64_t
using namespace std;

struct BIT {
    int n;
    vector<int> t;
    explicit BIT(int n=0): n(n) { t.assign(n+1, 0); }
    explicit BIT(const vector<int> &v) {
        n=v.size()-1;
        t.assign(n+1, 0);
        for (int i=1; i<=n; i++) {
            t[i]+=v[i];
            int j=i+(i&-i);
            if (j<=n) t[j]+=t[i];
        }
    }

    void add(int i, int v) {
        for (; i<=n; i+=i&-i) t[i]+=v;
    }
    int sum(int i) const {
        int r=0;
        for (; i>0; i-=i&-i) r+=t[i];
        return r;
    }
    int sum(int l, int r) const {
        if (l>r) return 0;
        return sum(r)-sum(l-1);
    }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n;
    vector<int> v(n+1), diff(n+1);
    for (int i=1; i<=n; i++) cin >> v[i];
    diff[1]=v[1];
    for (int i=2; i<=n; i++) diff[i]=v[i]-v[i-1];
    BIT tree(diff);

    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t==1) {
            int l, r, k;
            cin >> l >> r >> k;
            tree.add(l, k);
            if (r<n) tree.add(r+1, -k);
        }
        else {
            int x;
            cin >> x;
            cout << tree.sum(x) << '\n';
        }
    }
}