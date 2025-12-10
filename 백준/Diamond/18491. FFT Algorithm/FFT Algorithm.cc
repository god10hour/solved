#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

inline lint pow(__int128 n, __int128 k, lint mod) {
    __int128 r=1;
    while (k) {
        if (k&1) r=r*n%mod;
        n=n*n%mod;
        k/=2;
    }
    return r;
}

class RNG {
public:
    static uint64_t xorshift64() {
        static uint64_t x=88172645463393265ull;
        x^=x<<7;
        x^=x>>9;
        return x;
    }
    static lint rand(lint l, lint r) {
        return l+xorshift64()%(r-l+1);
    }
};

constexpr lint base[] {
    2, 325, 9375, 28178, 450775, 9780504, 1795265022
};
bool prime(lint n) {
    if (n<2 || n%6%4!=1) return (n|1)==3;
    for (int p: base) {
        if (p*p>n) break;
        if (n%p==0)
            return n==p;
    }
    lint d=n-1, s=__builtin_ctzll(d);
    d>>=s;
    for (int a: base) {
        lint p=pow(a%n, d, n), k=s;
        while (p!=1 && p!=n-1 && a%n && k--)
            p=(__int128)p*p%n;
        if (p!=n-1 && k!=s) return 0;
    }
    return 1;
}

lint div(lint n) {
    while (1) {
        lint c=RNG::rand(0, n-1);
        lint y=RNG::rand(2, n-2);
        auto step=[&](lint x)->lint {
            return ((__int128)x*x+c)%n;
        };

        lint m=256, d=1, r=1, q=1;
        while (d==1) {
            lint x=y;
            for (lint i=0; i<r; i++)
                y=step(y);

            lint k=0;
            while (k<r && d==1) {
                lint lim=min(m, r-k);
                for (lint i=0; i<lim; i++) {
                    y=step(y);
                    q=(__int128)q*llabs(x-y)%n;
                }
                d=gcd(q, n);
                k+=lim;
            }
            r<<=1;
        }
        if (d==n) {
            lint x=y;
            do {
                x=step(x);
                d=gcd(llabs(x-y), n);
            } while (d==1);
        }
        if (d!=n) return d;
    }
}

static void fact(lint n, vector<lint> &r) {
    if (n==1) return;
    if (prime(n)) {
        r.push_back(n);
        return;
    }
    lint d=div(n);
    fact(d, r);
    fact(n/d, r);
}

vector<lint> factor(lint n) {
    vector<lint> r;
    for (int p: base)
        while (n%p==0)
            r.push_back(p), n/=p;
    if (n>1) fact(n, r);
    sort(r.begin(), r.end());
    return r;
}

lint lambda(const vector<lint> &v) {
    lint s=1;
    for (int i=0; i<v.size();) {
        lint p=v[i];
        int j=i;
        while (j<v.size() && v[j]==p) j++;
        int e=j-i;
        lint cur;
        if (p==2) {
            if (e<3) cur=e;
            else cur=1LL<<(e-2);
        }
        else {
            __int128 pe=1;
            for (int k=0; k<e-1; k++)
                pe=pe*p;
            pe=pe*(p-1);
            cur=pe;
        }
        s=s/gcd(s, cur)*cur;
        i=j;
    }
    return s;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    lint n=100, m, k;
    cin >> m >> k;
    k=1LL<<k;
    auto a=factor(m);
    auto f=factor(k);
    f.erase(unique(f.begin(), f.end()), f.end());
    lint lam=lambda(a), G=-1;
    if (lam%k) return !(cout << -1);

    for (int i=0; i<n; i++) {
        lint x;
        do x=RNG::rand(2, m-1); while (gcd(x, m)!=1);
        lint g=pow(x, lam/k, m);
        auto valid=[&](lint u) {
            if (pow(u, k, m)!=1) return false;
            for (lint p: f)
                if (pow(u, k/p, m)==1)
                    return false;
            return true;
        };
        if (valid(g)) {
            G=g;
            break;
        }
    }
    cout << G << '\n';
}