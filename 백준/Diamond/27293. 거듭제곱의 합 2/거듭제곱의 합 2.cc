#ifdef _WIN32
#define getchar_unlocked getchar
#endif

#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr int mod=1e9+7;
constexpr int lim=1e5+7;

lint pow_mod(lint n, lint k) {
    lint r=1;
    while (k) {
        if (k&1) r=r*n%mod;
        n=n*n%mod;
        k>>=1;
    }
    return r;
}

static int read_int() {
    int c=getchar_unlocked();
    while (c<=' ') c=getchar_unlocked();
    int sgn=1, x=0;
    if (c=='-') sgn=-1, c=getchar_unlocked();
    while (c>' ') {
        x=x*10+(c-'0');
        c=getchar_unlocked();
    }
    return x*sgn;
}

int main() {
    int q=read_int();
    static array<lint, lim> y{}, fact{}, ifac{};
    static array<lint, lim+1> pre{}, suf{};
    fact[0]=1;
    for (int i=1; i<lim; i++)
        fact[i]=fact[i-1]*i%mod;
    ifac[lim-1]=pow_mod(fact[lim-1], mod-2);
    for (int i=lim-1; i>0; i--)
        ifac[i-1]=ifac[i]*i%mod;

    auto eval=[&](lint n, int d)->lint {
        if (n<=0) return 0;
        y[0]=0;
        for (int i=1; i<d+2; i++) {
            y[i]=y[i-1]+pow_mod(i, d);
            if (y[i]>=mod) y[i]-=mod;
        }
        if (n<=d+1) return y[n];

        pre[0]=1;
        for (int i=0; i<d+2; i++) {
            lint t=(n-i)%mod;
            if (t<0) t+=mod;
            pre[i+1]=t*pre[i]%mod;
        }
        suf[d+2]=1;
        for (int i=d+1; i>=0; i--) {
            lint t=(n-i)%mod;
            if (t<0) t+=mod;
            suf[i]=t*suf[i+1]%mod;
        }

        lint r=0;
        for (int i=0; i<d+2; i++) {
            lint k=pre[i]*suf[i+1]%mod;
            lint coef=ifac[i]*ifac[d-i+1]%mod;
            if ((d-i+1)&1) coef=(mod-coef)%mod;
            r=(r+y[i]*k%mod*coef)%mod;
        }
        return r;
    };

    while (q--) {
        lint a=read_int(), b=read_int();
        int d=read_int();

        lint sb=eval(b, d), sa=eval(a-1, d);
        printf("%lld\n", (sb-sa+mod)%mod);
    }
}