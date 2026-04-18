#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

template<int mod>
struct Mint {
    int v;
    Mint(): v(0) {}
    Mint(const lint x) {
        v=x>=-mod && x<mod? x: x%mod;
        if (v<0) v+=mod;
    }

    friend istream &operator>>(istream &is, Mint &a) {
        lint t; is >> t;
        a=Mint(t);
        return is;
    }
    friend ostream &operator<<(ostream &os, const Mint &a) {
        return os << a.v;
    }
    friend bool operator==(const Mint &a, const Mint &b) { return a.v==b.v; }
    friend bool operator!=(const Mint &a, const Mint &b) { return a.v!=b.v; }

    friend Mint pow(Mint n, lint k) {
        Mint r=1;
        while (k) {
            if (k&1) r*=n;
            n*=n;
            k>>=1;
        }
        return r;
    }
    friend Mint inv(const Mint a) {
        return pow(a, mod-2);
    }
    Mint operator-() const { return Mint(-v); }
    Mint &operator+=(const Mint a) {
        if ((v+=a.v)>=mod) v-=mod;
        return *this;
    }
    Mint &operator-=(const Mint a) {
        if ((v-=a.v)<0) v+=mod;
        return *this;
    }
    Mint &operator*=(const Mint a) {
        v=1LL*v*a.v%mod;
        return *this;
    }
    Mint &operator/=(const Mint a) {
        *this*=inv(a);
        return *this;
    }
    friend Mint operator+(Mint a, Mint b) { a+=b; return a; }
    friend Mint operator-(Mint a, Mint b) { a-=b; return a; }
    friend Mint operator*(Mint a, Mint b) { a*=b; return a; }
    friend Mint operator/(Mint a, Mint b) { a/=b; return a; }

    explicit operator int32_t() const { return v; }
    explicit operator int64_t() const { return v; }
};
constexpr int mod=1000000007;
using mint=Mint<mod>;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    lint n, L, k;
    cin >> n >> L >> k;

    vector<lint> fac;
    bool z=false;
    lint x=L;
    for (lint p=2; p<=x/p; p+=1+p%2) {
        if (x%p) continue;
        int c=0;
        while (x%p==0) x/=p, c++;
        if (c>=2) z=true;
        fac.push_back(p);
    }
    if (x>1) fac.push_back(x);
    if (z) return !(cout << 0 << '\n');
    mint muL=fac.size()&1? mint(-1): mint(1);

    vector<lint> use, smooth;
    for (lint p: fac) if (p<=n) use.push_back(p);
    auto dfs=[&](auto &&self, int i, lint cur)->void {
        if (i==use.size()) {
            smooth.push_back(cur);
            return;
        }
        self(self, i+1, cur);
        lint v=cur;
        while (v<=n/use[i]) v*=use[i], self(self, i+1, v);
    };
    dfs(dfs, 0, 1);
    ranges::sort(smooth);

    unordered_map<lint, mint> memo;
    memo.reserve(1<<20);
    auto G=[&](auto &&self, lint n)->mint {
        if (n<2) return max<lint>(n, 0);
        if (auto it=memo.find(n); it!=memo.end()) return it->second;
        mint s=ranges::upper_bound(smooth, n)-smooth.begin();
        for (lint l=2, r; l<=n; l=r+1) {
            lint q=n/l; r=n/q;
            s-=mint(r-l+1)*self(self, q);
        }
        memo[n]=s;
        return s;
    };

    mint s=0;
    for (lint l=1, r; l<=n; l=r+1) {
        lint q=n/l; r=n/q;
        mint seg=G(G, r)-G(G, l-1);
        s+=seg*pow(mint(q), k);
    }
    cout << s*muL << '\n';
}