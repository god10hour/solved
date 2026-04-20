#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr int mod=1e9-401;

int pow_mod(int n, int k) {
    int r=1;
    while (k) {
        if (k&1) r=1LL*r*n%mod;
        n=1LL*n*n%mod;
        k>>=1;
    }
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> part(n+1);
    part[0]=1;
    for (int i=1; i<=n; i++) {
        lint v=0;
        for (lint k=1; ; k++) {
            int g1=k*(k*3-1)/2, g2=k*(k*3+1)/2;
            int s=(k&1)*2-1;
            if (i<min(g1, g2)) break;
            if (i>=g1) v+=s*part[i-g1];
            if (i>=g2) v+=s*part[i-g2];
            v%=mod-1;
            if (v<0) v+=mod-1;
        }
        part[i]=v;
    }
    cout << pow_mod(m, part[n]) << '\n';
}
