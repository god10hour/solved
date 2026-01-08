#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr int mod=1e9+7;
constexpr int lim=1e6+1;

lint pow_mod(lint n, lint k) {
    lint r=1;
    while (k) {
        if (k&1) r=r*n%mod;
        n=n*n%mod;
        k>>=1;
    }
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    lint n, v;
    cin >> n >> v;
    vector<int8_t> mu(lim, 0);
    vector<int> prime, pMu(lim, 0);
    vector sieve(lim, true);
    prime.reserve(80000);
    mu[1]=1;
    for (int i=2; i<lim; i++) {
        if (sieve[i]) {
            prime.push_back(i);
            mu[i]=-1;
        }
        for (int p: prime) {
            lint x=1LL*i*p;
            if (x>=lim) break;
            sieve[x]=false;
            if (i%p==0) {
                mu[x]=0;
                break;
            }
            mu[x]=-mu[i];
        }
    }
    for (int i=1; i<lim; i++) pMu[i]=pMu[i-1]+mu[i];

    unordered_map<lint, int> memo;
    memo.reserve(1<<20);
    memo.max_load_factor(0.7);
    function<lint(lint)> M=[&](lint x) {
        if (x<lim) return pMu[x];
        if (
            auto it=memo.find(x);
            it!=memo.end()
        ) return int(it->second);
        lint rs=1;
        for (lint l=2; l<=x; ) {
            lint t=x/l, r=x/t;
            rs-=(r-l+1)*M(t);
            l=r+1;
        }
        return memo[x]=rs;
    };

    vector S(v+1, vector(v+1, 0));
    vector<int> T(v+1, 0), inv(v+2, 0);
    S[0][0]=1;
    for (int i=1; i<=v; i++)
        for (int k=1; k<=i; k++)
            S[i][k]=(S[i-1][k-1]+1LL*k*S[i-1][k])%mod;
    for (int k=1; k<=v; k++) {
        lint s=0;
        for (int i=k; i<=v; i++) {
            s+=S[i][k];
            if (s>=mod) s-=mod;
            if (s<0) s+=mod;
        }
        T[k]=s;
    }
    for (int i=1; i<=v+1; i++) inv[i]=pow_mod(i, mod-2);

    auto F=[&](lint x)->lint {
        // F(t) = sum_{m=1..x} sum_{u=1..v} m^u
        // = sum_{k=1..v} T[k] * (x+1)_{k+1} / (k+1)
        lint cur=1, rs=0;
        for (int i=1; i<=v+1; i++) {
            lint fact=(x+2-i)%mod;
            if (fact<0) fact+=mod;
            cur=cur*fact%mod;

            if (i>=2) {
                lint term=1LL*T[i-1]*cur%mod;
                term=term*inv[i]%mod;
                rs+=term;
                if (rs>=mod) rs-=mod;
                if (rs<0) rs+=mod;
            }
        }
        return rs;
    };

    lint rs=0;
    for (lint l=1; l<=n; ) {
        lint t=n/l, r=n/t;
        lint term=(M(r)-M(l-1))%mod;
        if (term<0) term+=mod;

        rs+=term*F(t)%mod;
        if (rs>=mod) rs-=mod;
        if (rs<0) rs+=mod;
        l=r+1;
    }
    cout << rs << '\n';
}