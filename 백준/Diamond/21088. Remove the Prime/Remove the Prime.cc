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
    lint d=n-1;
    int s=__builtin_ctzll(d);
    d>>=s;

    auto f=[&](lint a)->bool {
        if (a%n==0) return 1;
        lint x=pow(a, d, n);
        if (x==1 || x==n-1) return 1;
        for (int r=1; r<s; r++) {
            x=__int128(x)*x%n;
            if (x==n-1) return 1;
            if (x==1) return 0;
        }
        return 0;
    };

    for (lint a: base) if (!f(a))
        return 0;
    return 1;
}

lint div(lint n) {
    while (1) {
        lint c=RNG::rand(0, n-1);
        lint y=RNG::rand(2, n-2);
        auto step=[&](lint x)->lint {
            return (__int128(x)*x+c)%n;
        };

        lint m=64, d=1, r=1, q=1;
        while (d==1) {
            lint x=y, k=0;
            for (lint i=0; i<r; i++) y=step(y);
            while (k<r && d==1) {
                lint lim=min(m, r-k);
                for (lint i=0; i<lim; i++) {
                    y=step(y);
                    q=__int128(q)*llabs(x-y)%n;
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
                d=__gcd(x-y>0? x-y: y-x, n);
            } while (d==1);
        }
        if (d!=n) return d;
    }
}

static void fact(lint n, lint &r) {
    if (n<2 || n<=r) return;
    if (prime(n)) {
        r=max(r, n);
        return;
    }
    lint d=div(n);
    fact(d, r);
    fact(n/d, r);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<lint> v(n+1, 0);
    unordered_map<lint, vector<lint>> factor;
    for (int i=1; i<=n; i++) {
        cin >> v[i];
        while (v[i]>1LL) {
            lint r=0;
            fact(v[i], r);
            factor[r].emplace_back(i);
            while (v[i]%r==0) v[i]/=r;
        }
    }

    lint rs=0;
    for (const auto &vec: factor|views::values) {
        int k=0, s=vec.size();
        for (int i=0; i<s; i++, k++)
            if (i==0 || vec[i]!=vec[i-1]+1)
                rs^=k, k=0;
        rs^=k;
    }
    cout << (rs? "First": "Second") << '\n';
}