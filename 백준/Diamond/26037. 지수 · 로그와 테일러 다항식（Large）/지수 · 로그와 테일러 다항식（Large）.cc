#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const int MOD=998244353;
const int ROOT=3;

struct Poly {
    static int lim;
    vector<int> v;
    Poly() {}
    explicit Poly(int n): v(n, 0) {}
    explicit Poly(const vector<int> &v): v(v) {}
    explicit Poly(vector<int> &&v): v(move(v)) {}

    int size() const {return v.size();}
    void resize(int n) {v.resize(n);}
    int &operator[](int i) {return v[i];}
    void selfcut(int m) {
        if (m<v.size()) v.resize(m);
    }
    vector<int> cut(int m) {
        if (m>=v.size())
            return v;
        return vector(v.begin(), v.begin()+m);
    }

    static int POW(int n, int k) {
        int r=1;
        while (k) {
            if (k&1)
                r=r*n%MOD;
            n=n*n%MOD;
            k/=2;
        }
        return r;
    }

    void NTT(bool inv) {
        int s=v.size();
        for (int i=1, j=0; i<s; i++) {
            int b=s/2;
            while (j>=b)
                j-=b, b/=2;
            j+=b;
            if (i<j) swap(v[i], v[j]);
        }
        for (int k=1; k<s; k*=2) {
            int w=POW(ROOT, (MOD-1)/(k*2));
            if (inv) w=POW(w, MOD-2);
            for (int i=0; i<s; i+=k*2) {
                int uni=1;
                for (int j=0; j<k; j++) {
                    int a=v[i+j];
                    int b=v[i+j+k]*uni%MOD;
                    v[i+j]=(a+b)%MOD;
                    v[i+j+k]=(a-b+MOD)%MOD;
                    uni=uni*w%MOD;
                }
            }
        }
        if (inv) {
            int I=POW(s, MOD-2);
            for (int i=0; i<s; i++)
                v[i]=v[i]*I%MOD;
        }
    }
    static Poly CVL(const Poly &V, const Poly &U) {
        Poly v=V, u=U;
        int s=1, n=v.size()+u.size()-1;
        while (s<n)
            s*=2;
        v.resize(s), v.NTT(0);
        u.resize(s), u.NTT(0);
        for (int i=0; i<s; i++)
            v[i]=v[i]*u[i]%MOD;
        v.NTT(1), v.resize(n);
        return v;
    }

    Poly operator+(const Poly &o) const {
        int s=max(size(), o.size());
        if (lim>0) s=min(s, lim);
        Poly r(s);
        for (int i=0; i<s; i++) {
            int x=i<size()? v[i]:0;
            int y=i<o.size()? o.v[i]:0;
            r[i]=(x+y)%MOD;
        }
        return r;
    }
    Poly operator-(const Poly &o) const {
        int s=max(size(), o.size());
        if (lim>0) s=min(s, lim);
        Poly r(s);
        for (int i=0; i<s; i++) {
            int x=i<size()? v[i]:0;
            int y=i<o.size()? o.v[i]:0;
            r[i]=(x-y+MOD)%MOD;
        }
        return r;
    }
    Poly operator*(const Poly &o) const {
        if (lim>0) {
            Poly w=CVL(*this, o);
            if (lim>0 && w.size()>lim)
                w.resize(lim);
            return w;
        }
        return CVL(*this, o);
    }

    static void set(int m) {lim=m;}
    static void clear() {lim=-1;}
    void trim() {
        while (!v.empty() && v.back()==0)
            v.pop_back();
    }

    Poly inverse(int m) const {
        Poly a=*this;
        a.selfcut(m);
        Poly b(1);
        b[0]=POW(a.v[0], MOD-2);
        int s=1;
        while (s<m) {
            int x=min(m, s*2), pre=lim;
            set(x);
            Poly a2=a; a2.selfcut(x);
            Poly ab=a2*b, E(x);
            E[0]=(2-ab.v[0]+MOD)%MOD;
            for (int i=1; i<x; i++)
                E[i]=(0-(i<ab.size()? ab.v[i]:0)+MOD)%MOD;
            b=b*E;
            set(pre);
            s=x;
        }
        b.selfcut(m);
        return b;
    }
};
int Poly::lim=-1;

Poly deriv(const Poly &v) {
    int n=v.size();
    if (n<2) return Poly();
    Poly D(n-1);
    for (int i=1; i<n; i++)
        D[i-1]=i*v.v[i]%MOD;
    return D;
}
Poly integ(const Poly &v, const vector<int> &inv, int cap=-1) {
    int n=v.size();
    Poly I(n+1);
    for (int i=0; i<n; i++)
        I[i+1]=inv[i+1]*v.v[i]%MOD;
    if (cap>0 && I.size()>cap) I.resize(cap);
    return I;
}

Poly log(const Poly &v, int m, const vector<int> &inv) {
    Poly D=deriv(v), vinv=v.inverse(m);
    int pre=Poly::lim;
    Poly::set(m-1);
    Poly Q=D*vinv;
    Poly::set(pre);
    Poly L=integ(Q, inv, m);
    L.selfcut(m);
    return L;
}
Poly exp(const Poly &v, int m, const vector<int> &inv) {
    Poly F(1);
    F[0]=1;
    int s=1;
    while (s<m) {
        int x=min(m, s*2);
        Poly F2=F; F2.selfcut(x);
        Poly Ln=log(F2, x, inv);
        Poly v2=v; v2.selfcut(x);
        int pre=Poly::lim;
        Poly::set(x);
        Poly del=v2-Ln;
        if (del.size()==0) del.resize(1);
        del[0]=(del[0]+1)%MOD;
        F=F*del;
        Poly::set(pre);
        s=x;
    }
    F.selfcut(m);
    return F;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    Poly P(n+1);
    for (int i=0; i<n+1; i++)
        cin >> P[i];
    vector<int> inv(n+2, 1);
    for (int i=2; i<n+2; i++)
        inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;

    Poly L=P;
    L[0]=(L[0]+1)%MOD;
    L=log(L, n+1, inv);
    Poly E=exp(P, n+1, inv);
    if (E.size()==0) E.resize(1);
    E[0]=(E[0]-1+MOD)%MOD;

    for (int i=0; i<n+1; i++)
        cout << L[i] << ' ';
    cout << '\n';
    for (int i=0; i<n+1; i++)
        cout << E[i] << ' ';
    cout << '\n';
}