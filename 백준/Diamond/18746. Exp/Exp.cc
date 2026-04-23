#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr int mod=998244353;

int pow_mod(int n, int k) {
    int r=1;
    while (k) {
        if (k&1) r=lint(r)*n%mod;
        n=lint(n)*n%mod;
        k>>=1;
    }
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, k, x;
    cin >> n >> k >> x;

    int den=pow_mod(10000, mod-2);
    vector<int> a(k+1), inv(x+1), c(x);
    for (int i=0; i<=k; i++) {
        string s;
        cin >> s;
        a[i]=lint(stoi(s.substr(2)))*den%mod;
    }
    inv[1]=1;
    for (int i=2; i<=x; i++) inv[i]=lint(mod-mod/i)*inv[mod%i]%mod;
    int a0_inv=pow_mod(a[0], mod-2);
    c[0]=pow_mod(a[0], n);

    int r=x%mod;
    for (int s=0; s<x; s++) {
        r=(r-lint(x-s)*c[s])%mod;
        if (s==x-1) break;

        lint sum=0;
        for (int i=1; i<=min(k, s+1); i++) {
            int coef=((lint(n+1)*i-(s+1))%mod+mod)%mod;
            sum=(sum+lint(coef)*a[i]%mod*c[s+1-i])%mod;
        }
        c[s+1]=sum*inv[s+1]%mod*a0_inv%mod;
    }
    if (r<0) r+=mod;
    cout << r << '\n';
}