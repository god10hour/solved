#include <bits/stdc++.h>
using namespace std;
constexpr int MOD=998244353;

template<int mod>
struct Mint {
    int v;
    Mint(): v(0) {}
    explicit Mint(const int64_t x) {
        v=x>=-mod && x<mod? x: x%mod;
        if (v<0) v+=mod;
    }

    friend istream &operator>>(istream &is, Mint &a) {
        int64_t t; is >> t;
        a=Mint(t);
        return is;
    }
    friend ostream &operator<<(ostream &os, const Mint &a) {
        return os << a.v;
    }
    friend bool operator==(const Mint &a, const Mint &b) { return a.v==b.v; }
    friend bool operator!=(const Mint &a, const Mint &b) { return a.v!=b.v; }

    friend Mint pow(Mint n, int k) {
        Mint r=Mint(1);
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
using Z=Mint<MOD>;

vector<Z> conv(const vector<Z> &v, const vector<Z> &u) {
    int n=v.size()-1;
    vector w(n+1, Z(0));
    for (int i=1; i<=n; i++) {
        if (v[i]==Z(0)) continue;
        int lim=n/i;
        for (int j=1; j<=lim; j++) {
            if (u[j]==Z(0)) continue;
            w[i*j]+=v[i]*u[j];
        }
    }
    return w;
}

vector<Z> dlog(const vector<Z> &v) {
    int n=v.size()-1, L=0;
    while (1<<(L+1)<=n) L++;
    vector<Z> u=v;
    u[1]-=Z(1);
    vector<Z> p=u, r(n+1, Z(0));
    for (int m=1; m<=L; m++) {
        Z coef=Z(1)/Z(m);
        if (m%2==0) coef=-coef;
        for (int i=1; i<=n; i++) r[i]+=p[i]*coef;
        if (m!=L) p=conv(p, u);
    }
    r[1]=Z(0);
    return r;
}

vector<Z> dexp(const vector<Z> &v) {
    int n=v.size()-1, L=0;
    while (1<<(L+1)<=n) L++;
    vector<Z> p=v, r(n+1, Z(0));
    r[1]=Z(1);
    Z fac=Z(1);
    for (int m=1; m<=L; m++) {
        fac*=Z(m);
        Z ifac=inv(fac);
        for (int i=1; i<=n; i++) r[i]+=p[i]*ifac;
        if (m!=L) p=conv(p, v);
    }
    r[1]=Z(1);
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int64_t n, k;
    cin >> n >> k;
    vector<Z> g(n+1);
    for (int i=1; i<=n; i++) cin >> g[i];
    Z kinv=inv(Z(k));
    vector<Z> lg=dlog(g);
    for (int i=1; i<=n; i++) lg[i]*=kinv;
    vector<Z> f=dexp(lg);

    for (int i=1; i<=n; i++) cout << f[i] << ' ';
}