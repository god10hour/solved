#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

struct BIT {
    int n;
    vector<lint> t;
    explicit BIT(int n=0): n(n) { t.assign(n+1, 0); }
    explicit BIT(const vector<lint> &v) {
        n=v.size()-1;
        t.assign(n+1, 0);
        for (int i=1; i<=n; i++) {
            t[i]+=v[i];
            int j=i+(i&-i);
            if (j<=n) t[j]+=t[i];
        }
    }

    void add(int i, lint v) {
        for (; i<=n; i+=i&-i) t[i]+=v;
    }
    lint sum(int i) const {
        lint r=0;
        for (; i>0; i-=i&-i) r+=t[i];
        return r;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n;
    vector<lint> v(n+1), diff(n+1);
    for (int i=1; i<=n; i++) cin >> v[i];
    diff[1]=v[1];
    for (int i=2; i<=n; i++) diff[i]=v[i]-v[i-1];
    BIT tree(diff);

    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t==1) {
            lint l, r, k;
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