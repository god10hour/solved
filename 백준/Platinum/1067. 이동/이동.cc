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

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, s=0;
    cin >> n;
    vector<int> V(n*2), U(n);
    for (int i=0; i<n; i++) cin >> V[i], V[i+n]=V[i];
    for (int i=0; i<n; i++) cin >> U[n-i-1];
    auto w=NTT<1224736769, 3>::conv(V, U);
    for (int i: w) s=max(s, i);
    cout << s << '\n';
}