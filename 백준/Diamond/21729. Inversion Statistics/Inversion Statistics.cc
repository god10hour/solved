#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr int mod=1e6+3;
vector<int> fac, ifac;

int pow_mod(int n, int k) {
    int r=1;
    while (k) {
        if (k&1) r=1LL*r*n%mod;
        n=1LL*n*n%mod;
        k>>=1;
    }
    return r;
}

int small(int n, int r) {
    return 1LL*fac[n]*ifac[r]%mod*ifac[n-r]%mod;
}
int binom(lint n, lint r) {
    if (r<0 || r>n) return 0;
    int C=1;
    while (n || r) {
        int ni=n%mod, ri=r%mod;
        if (ri>ni) return 0;
        C=1LL*C*small(ni, ri)%mod;
        n/=mod, r/=mod;
    }
    return C;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    fac.assign(mod, 1);
    ifac.assign(mod, 1);
    for (int i=1; i<mod; i++) fac[i]=1LL*fac[i-1]*i%mod;
    ifac[mod-1]=pow_mod(fac[mod-1], mod-2);
    for (int i=mod-1; i>0; i--) ifac[i-1]=1LL*ifac[i]*i%mod;
    
    int t;
    cin >> t;
    while (t--) {
        lint n, k;
        cin >> n >> k;
        auto contrib=[&](lint x)->int {
            if (x>k) return 0;
            lint cur=binom(n+k-x-1, k-x), r=k-x-n-1;
            (cur+=binom(n+r, r)-binom(r, r-n))%=mod;
            if (cur<0) cur+=mod;
            return cur;
        };

        int r=contrib(0);
        for (lint i=1; ; i++) {
            lint g1=i*(i*3-1)/2, g2=i*(i*3+1)/2;
            if (g1>k && g2>k) break;
            int sgn=i&1? -1: 1;
            if (g1<=k) r+=sgn*contrib(g1);
            if (g2<=k) r+=sgn*contrib(g2);
            r%=mod;
            if (r<0) r+=mod;
        }
        cout << r << '\n';
    }
}