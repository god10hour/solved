#include <bits/stdc++.h>
using namespace std;
const int MOD=1e9+7;

template<int mod>
struct Mint {
    int v;
    Mint(): v(0) {}
    Mint(int64_t x) {
        v=(x>=-mod && x<mod? x: x%mod);
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
        v=(int64_t)v*a.v%mod;
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

    operator int32_t() const { return v; }
    operator int64_t() const { return v; }
};
using Z=Mint<MOD>;

static void trim(vector<Z> &p) {
    while (!p.empty() && p.back()==Z(0))
        p.pop_back();
}
static int deg(const vector<Z> &p) {
    return p.size()-1;
}

vector<Z> polyMod(vector<Z> u, const vector<Z> &v) {
    trim(u);
    if (u.empty()) return {};
    if (v.empty()) return {};

    int dv=deg(v);
    while (!u.empty() && deg(u)>=dv) {
        int d=deg(u)-dv;
        Z coef=u.back();
        for (int i=0; i<dv+1; i++)
            u[d+i]-=coef*v[i];
        trim(u);
    }
    return u;
}

Z resultant(int L, vector<Z> v) {
    trim(v);
    if (v.empty()) return Z(0);

    vector<Z> u(L+1, Z(0));
    u[L]=Z(1), u[0]-=Z(1);
    Z r=Z(1);
    int du=L, dv=deg(v);

    while (dv>0) {
        if (du&1 && dv&1)
            r*=Z(MOD-1);
        Z lc=v.back();
        if (lc!=Z(1)) {
            Z i=inv(lc);
            for (auto &x: v)
                x*=i;
            r*=pow(lc, du);
        }
        vector<Z> w=polyMod(u, v);
        if (w.empty()) return Z(0);
        u.swap(v), du=dv;
        v.swap(w), dv=deg(v);
    }
    Z c=v.empty()? Z(0): v[0];
    if (c==Z(0)) return Z(0);
    r*=pow(c, du);
    return r;
}

struct BIT {
    int n;
    vector<int> t;
    BIT(int n): n(n), t(n+1, 0) {}
    void add(int i, int v) {
        for (++i; i<=n; i+=i&-i)
            t[i]+=v;
    }
    int sum(int i) {
        int s=0;
        for (++i; i>0; i-=i&-i)
            s+=t[i];
        return s;
    }
};
bool inversion(const vector<int> &C) {
    int n=C.size();
    BIT bit(n);
    int64_t inv=0;
    for (int i=n-1; i>=0; i--) {
        inv+=bit.sum(C[i]-1);
        bit.add(C[i], 1);
    }
    return inv&1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int64_t> a(n), pi(n);
    for (int i=0; i<n; i++) cin >> a[i];
    for (int i=0; i<n; i++) cin >> pi[i], pi[i]--;

    Z r=Z(1);
    int cyc=0;
    vector<int> vis(n, 0), C;
    for (int i=0; i<n; i++) if (!vis[i]) {
        cyc++;
        if (cyc>1) return !(cout << 0);
        int t=i;
        while (!vis[t]) {
            vis[t]=1;
            C.push_back(t);
            t=pi[t];
        }
    }
    int L=C.size();
    vector<Z> v(L);
    for (int j=0; j<L; j++) v[j]=Z(a[C[j]]);
    r*=resultant(L, v);
    Z s=(n-1)*(n-2)/2%2? Z(-1): Z(1);
    s*=inversion(C)? Z(-1): Z(1);
    cout << s*r;
}