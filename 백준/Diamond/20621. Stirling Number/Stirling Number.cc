#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr int N=1e6+1;
array<int, N> fac, ifac, inv, pws, rise;

inline int pow(lint n, int k, int mod) {
    lint r=1;
    while (k) {
        if (k&1) r=r*n%mod;
        n=n*n%mod;
        k>>=1;
    }
    return r;
}

int find_g(int x) {
    static array<int, 16> a;
    int c=0, k=x-1;
    for (int i=2; i*i<=k; i++) {
        if (k%i) continue;
        a[++c]=i;
        while (k%i==0) k/=i;
    }
    if (k>1) a[++c]=k;
    for (int i=2; i<=x; i++) {
        bool z=true;
        for (int j=1; j<=c; j++) {
            if (pow(i, (x-1)/a[j], x)!=1) continue;
            z=false;
            break;
        }
        if (z) return i;
    }
    return -1;
}

int binom(lint n, lint m, int p) {
    if (n<m) return 0;
    if (n>=p) return 1LL*binom(n/p, m/p, p)*binom(n%p, m%p, p)%p;
    return 1LL*fac[n]*ifac[m]%p*ifac[n-m]%p;
}

int sum(int n, int m, int p) {
    if (n==0) return 1;
    if (n<=m) return fac[n];
    int r=1LL*rise[0]*(m+1)%p;
    for (int j=1; j<p-1; j++) {
        lint top=1-pws[p-1-1LL*j*(m+1)%(p-1)]+p;
        lint bot=inv[p+1-pws[p-1-j]];
        r=(r+rise[j]*top*bot)%p;
    }
    return p-r;
}

int pref(lint n, lint m, int p) {
    lint L, q=n/p;
    int t, r=n%p;
    if (m<q) return 0;
    m-=q;
    t=m%(p-1), L=m/(p-1);
    int s=(
        +1LL*sum(r, t, p)*binom(q, L, p)
        -1LL*fac[r]*(L==0? 0: binom(q-1, L-1, p))
    )%p;
    return q-L&1? -s: s;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    lint n, l, r, p;
    cin >> n >> l >> r >> p;
    int g=find_g(p), u=n%p;

    pws[0]=inv[1]=fac[0]=fac[1]=ifac[0]=1;
    ifac[p-1]=p-1;
    for (int i=2; i<p; i++) fac[i]=lint(i)*fac[i-1]%p;
    for (int i=p-2; i>0; i--) ifac[i]=lint(i+1)*ifac[i+1]%p;
    for (int i=2; i<p; i++) inv[i]=lint(fac[i-1])*ifac[i]%p;
    for (int i=1; i<p-1; i++) pws[i]=lint(g)*pws[i-1]%p;
    for (int i=0; i<p-1; i++) rise[i]=pws[i]+u-1>=p? 0: lint(fac[pws[i]+u-1])*ifac[pws[i]-1]%p;

    cout << (pref(n, r, p)-pref(n, l-1, p)+p*2)%p << '\n';
}