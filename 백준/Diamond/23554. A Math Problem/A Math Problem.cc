#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr int mod=1e9+7;

int pow_mod(lint n, lint k) {
    lint r=1;
    while (k) {
        if (k&1) r=r*n%mod;
        n=n*n%mod;
        k>>=1;
    }
    return r;
}

int binom(int n, int k) {
    if (k<0 || k>n) return 0;
    lint r=1;
    for (int i=1; i<=k; i++)
        r=r*(n-i+1)/i%mod;
    return r;
}

int surject(lint n, lint r) {
    lint s=0;
    for (int i=0, d=1; i<=r; i++, d*=-1) {
        int cur=1LL*binom(r, i)*pow_mod(r-i, n)%mod;
        s=(s+d*cur+mod)%mod;
    }
    return s;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    vector<vector<pair<int, int>>> coef={
        {}, {},
        {{1, 2}},
        {{2, 6}},
        {{2, 12}, {3, 24}},
        {{3, 120}, {4, 120}},
        {{3, 720}, {4, 1080}, {5, 720}}
    };

    int t;
    cin >> t;
    while (t--) {
        lint n, k, s=0;
        cin >> n >> k;
        for (auto [r, c]: coef[k])
            s=(s+1LL*c*surject(n, r))%mod;
        cout << s << '\n';
    }
}