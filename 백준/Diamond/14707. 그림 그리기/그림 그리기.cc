#include <bits/stdc++.h>
using namespace std;

#define int int64_t
template<int mod, int root>
struct NTT {
    static int pow(int n, int k) {
        int r=1;
        while (k) {
            if (k&1)
                r=r*n%mod;
            n=n*n%mod;
            k/=2;
        }
        return r;
    }

    static void ntt(vector<int> &v, bool inv) {
        int s=v.size();
        for (int i=1, j=0; i<s; i++) {
            int b=s/2;
            while (j>=b)
                j-=b, b/=2;
            j+=b;
            if (i<j) swap(v[i], v[j]);
        }
        for (int k=1; k<s; k*=2) {
            int w=pow(root, (mod-1)/(k*2));
            if (inv) w=pow(w, mod-2);
            for (int i=0; i<s; i+=k*2) {
                int uni=1;
                for (int j=0; j<k; j++) {
                    int a=v[i+j];
                    int b=v[i+j+k]*uni%mod;
                    v[i+j]=(a+b)%mod;
                    v[i+j+k]=(a-b+mod)%mod;
                    uni=uni*w%mod;
                }
            }
        }
        if (inv) {
            int I=pow(s, mod-2);
            for (int i=0; i<s; i++)
                v[i]=v[i]*I%mod;
        }
    }

    static vector<int> conv(vector<int> V, vector<int> U) {
        if (V.empty() || U.empty())return {};
        int s=1, n=V.size()+U.size()-1;
        while (s<n) s*=2;
        for (auto &x: V) { x%=mod; if (x<0) x+=mod; }
        for (auto &x: U) { x%=mod; if (x<0) x+=mod; }
        V.resize(s); ntt(V, 0);
        U.resize(s); ntt(U, 0);
        for (int i=0; i<s; i++)
            V[i]=V[i]*U[i]%mod;
        ntt(V, 1), V.resize(n);
        return V;
    }
};

struct CRT {
    using u128=__uint128_t;
    static constexpr int MODS[3]={
        167772161, 469762049, 1224736769
    };
    static constexpr int ROOT=3;
    using P0=NTT<MODS[0], ROOT>;
    using P1=NTT<MODS[1], ROOT>;
    using P2=NTT<MODS[2], ROOT>;

    static int pow(int n, int k, int mod) {
        int r=1;
        while (k) {
            if (k&1)
                r=r*n%mod;
            n=n*n%mod;
            k/=2;
        }
        return r;
    }

    int combine(const int a[3]) {
        u128 r=0, mod=1;
        for (int i=0; i<3; i++) {
            int Mi=MODS[i], ri=r%Mi;
            if (ri<0) ri+=Mi;
            int diff=(a[i]+Mi-ri)%Mi;
            int inv=pow(mod%Mi, Mi-2, Mi);
            r+=mod*(diff*inv%Mi);
            mod*=Mi;
        }
        return r;
    }

    vector<int> conv(const vector<int> &V, const vector<int> &U) {
        if (V.empty() || U.empty()) return {};
        int n=V.size()+U.size()-1;
        array<vector<int>, 3> v, u;
        for (int i=0; i<3; i++) v[i].resize(V.size());
        for (int i=0; i<3; i++) u[i].resize(U.size());

        for (int i=0; i<V.size(); i++)
            for (int j=0; j<3; j++) {
                v[j][i]=V[i]%MODS[j];
                if (v[j][i]<0) v[j][i]+=MODS[j];
            }
        for (int i=0; i<U.size(); i++)
            for (int j=0; j<3; j++) {
                u[j][i]=U[i]%MODS[j];
                if (u[j][i]<0) u[j][i]+=MODS[j];
            }

        auto w0=P0::conv(v[0], u[0]);
        auto w1=P1::conv(v[1], u[1]);
        auto w2=P2::conv(v[2], u[2]);

        vector<int> r(n);
        for (int i=0; i<n; i++) {
            int a[3]={
                i<w0.size()? w0[i]:0,
                i<w1.size()? w1[i]:0,
                i<w2.size()? w2[i]:0
            };
            r[i]=combine(a);
        }
        return r;
    }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, L;
    CRT crt;
    cin >> n >> m >> L;
    vector<int> H(n), W(m);
    for (int i=0; i<n; i++) cin >> H[i];
    for (int i=0; i<m; i++) cin >> W[i];

    vector<int> A(L, 0), B(L, 0);
    for (int i=0; i<n; i++) A[i*m%L]+=H[i];
    for (int i=0; i<m; i++) B[i%L]+=W[i];
    auto C=crt.conv(A, B);
    C.push_back(0);
    for (int i=0; i<L; i++) cout << C[i]+C[i+L] << '\n';
}