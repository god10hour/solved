#include <bits/stdc++.h>
using namespace std;

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
using Z=Mint<998244353>;

constexpr int N=1e6;
Z f[N+5], g[N+5];
int prs[80005], pc;
uint8_t om[N+5];
Z invs[32];
bitset<N+5> sieve;

int init(int n) {
    sieve.set();
    sieve[0]=sieve[1]=0;
    for (int i=2; 1LL*i*i<=n; i++) if (sieve[i])
        for (int j=i*i; j<=n; j+=i) sieve[j]=0;
    pc=0;
    for (int i=2; i<=n; i++) if (sieve[i]) prs[pc++]=i;
    int M=0;
    for (int t=0; t<pc; t++) {
        int p=prs[t];
        for (int x=p; x<=n; x+=p) {
            int y=x;
            while (y%p==0) om[x]++, y/=p;
        }
    }
    for (int i=2; i<=n; i++) M=max<int>(M, om[i]);
    return M;
}

void lnO(Z *a, int n) {
    for (int i=1; i<=n; i++) g[i-1]=a[i-1]*Z(om[i]);
    for (int i=1; i<=n; i++) {
        for (int j=2; 1LL*i*j<=n; j++)
            g[i*j-1]-=g[i-1]*a[j-1];
        if (i>1) g[i-1]*=invs[om[i]];
    }
    for (int i=0; i<n; i++) a[i]=g[i];
}

void expO(Z *a, int n) {
    g[0]=Z(1);
    for (int i=1; i<n; i++) g[i]=Z(0);
    for (int i=1; i<=n; i++) a[i-1]*=Z((int)om[i]);
    for (int i=1; i<=n; i++) {
        if (i>1) g[i-1]*=invs[om[i]];
        for (int j=2; 1LL*i*j<=n; j++)
            g[i*j-1]+=g[i-1]*a[j-1];
    }
    for (int i=0; i<n; i++) a[i]=g[i];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    for (int i=0; i<n; i++) cin >> f[i];
    int M=init(n);

    invs[1]=Z(1);
    for (int i=2; i<=M; i++) invs[i]=inv(Z(i));

    Z ik=inv(Z(k));
    lnO(f, n);
    for (int i=0; i<n; i++) f[i]*=ik;
    expO(f, n);
    for (int i=0; i<n; i++) cout << f[i] << ' ';
}