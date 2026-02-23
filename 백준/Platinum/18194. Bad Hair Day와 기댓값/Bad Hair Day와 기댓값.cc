#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr int mod=1e9+7;

int inv(lint x) {
    lint r=1, k=mod-2;
    while (k) {
        if (k&1) r=r*x%mod;
        x=x*x%mod;
        k>>=1;
    }
    return r;
}
int frac(lint a, lint b) {
    return a*inv(b)%mod;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto &x: v) cin >> x;
    ranges::sort(v);

    lint r=0;
    for (auto &x: v) {
        int a=ranges::lower_bound(v, x)-v.begin();
        int b=n-a;
        r+=frac(a, b+1);
    }
    cout << r%mod << '\n';
}