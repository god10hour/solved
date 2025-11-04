#include <bits/stdc++.h>
using namespace std;
constexpr int MOD=998244353;

template<int mod, int root>
struct NTT {
    static int pow(int n, int k) {
        int r=1;
        while (k) {
            if (k&1)
                r=1LL*r*n%mod;
            n=1LL*n*n%mod;
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
                    int a=1LL*v[i+j];
                    int b=1LL*v[i+j+k]*uni%mod;
                    v[i+j]=(1LL*a+b)%mod;
                    v[i+j+k]=(1LL*a-b+mod)%mod;
                    uni=1LL*uni*w%mod;
                }
            }
        }
        if (inv) {
            int I=pow(s, mod-2);
            for (int i=0; i<s; i++)
                v[i]=1LL*v[i]*I%mod;
        }
    }

    static vector<int> conv(vector<int> v, vector<int> u) {
        if (v.empty() || u.empty()) return {};
        int s=1, n=v.size()+u.size()-1;
        while (s<n) s*=2;
        v.resize(s); ntt(v, 0);
        u.resize(s); ntt(u, 0);
        for (int i=0; i<s; i++)
            v[i]=1LL*v[i]*u[i]%mod;
        ntt(v, 1), v.resize(n);
        return v;
    }
};
NTT<MOD, 3> ntt;

struct CPoly {
    vector<int> rea, ima;
    CPoly(int n) {
        rea.assign(n, 0);
        ima.assign(n, 0);
    }
    size_t size() const { return rea.size(); };
    void resize(size_t n) {
        rea.assign(n, 0);
        ima.assign(n, 0);
    };

    CPoly operator*(const CPoly &o) const {
        auto S1=ntt.conv(rea, o.rea);
        auto S2=ntt.conv(ima, o.ima);
        vector<int> A(size()), B(o.size());
        for (int i=0; i<size(); i++) A[i]=(1LL*rea[i]+ima[i])%MOD;
        for (int i=0; i<o.size(); i++) B[i]=(1LL*o.rea[i]+o.ima[i])%MOD;
        auto S3=ntt.conv(A, B);
        int n=S3.size();
        CPoly C(n);
        for (int i=0; i<n; i++) {
            C.rea[i]=(1LL*S1[i]-S2[i]+MOD)%MOD;
            C.ima[i]=(1LL*S3[i]-S1[i]-S2[i]+MOD*2)%MOD;
        }
        return C;
    }
};

CPoly make(int a, int b) {
    CPoly P(2);
    P.rea[0]=(MOD-a)%MOD;
    P.ima[0]=(MOD-b)%MOD;
    P.rea[1]=1;
    P.ima[1]=0;
    return P;
}

CPoly build(const vector<pair<int, int>> &pts, int L, int R) {
    if (R-L==1)
        return make(pts[L].first, pts[L].second);
    int M=(L+R)/2;
    auto LP=build(pts, L, M);
    auto RP=build(pts, M, R);
    return LP*RP;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, r;
    int64_t A=0, k=1;
    cin >> n >> r;
    vector<pair<int, int>> pts(n);
    for (auto &[x, y]: pts)
        cin >> x >> y;
    auto Q=build(pts, 0, n);
    r=1LL*r*r%MOD;
    for (int i=0; i<Q.size(); i++) {
        int64_t c=(1LL*Q.rea[i]*Q.rea[i]+1LL*Q.ima[i]*Q.ima[i])%MOD;
        A+=(__int128)c*k*ntt.pow(i+1, MOD-2)%MOD;
        if (A>=MOD) A-=MOD;
        k=k*r%MOD;
    }
    cout << A << '\n';
}