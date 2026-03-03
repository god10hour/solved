#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    array<lint, 3> a={};
    vector<pair<int, int>> r;
    for (auto &i: a) cin >> i;

    auto pour=[&](int don, int rec) {
        a[don]-=a[rec];
        a[rec]+=a[rec];
        r.emplace_back(don, rec);
    };
    auto msb_idx=[&](lint v) {
        return 63-__builtin_clzll(v);
    };

    while (min({a[0], a[1], a[2]})>0) {
        array idx={0, 1, 2};
        ranges::sort(idx, [&](int i, int j) {
            return a[i]<a[j];
        });
        int x=idx[0], y=idx[1], z=idx[2];

        if (a[y]%a[x]<=a[x]/2) {
            int q=a[y]/a[x], lim=msb_idx(q);
            for (int i=0; i<=lim; i++)
                pour(q>>i&1? y: z, x);
        }
        else {
            int q=(a[y]+a[x]-1)/a[x], lim=msb_idx(q);
            for (int i=0; i<lim; i++)
                pour(q>>i&1? y: z, x);
            pour(x, y);
        }
    }

    cout << r.size() << '\n';
    for (auto &[i, j]: r)
        cout << i+1 << ' ' << j+1 << '\n';
}