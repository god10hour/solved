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
                v[i]=(int64_t)v[i]*I%mod;
        }
    }

    static vector<int> conv(vector<int> v, vector<int> u, int k) {
        if (v.empty() || u.empty())return {};
        int s=1, n=v.size()+u.size()-1;
        while (s<n) s*=2;
        v.resize(s); ntt(v, 0);
        u.resize(s); ntt(u, 0);
        for (int i=0; i<s; i++)
            v[i]=1LL*v[i]*u[i]%mod;
        ntt(v, 1), v.resize(min(n, k));
        return v;
    }
};

vector<int> product(const vector<int> &G, int upto, int k) {
    if (!upto) return {1};
    vector<vector<int>> v;
    v.reserve(upto);
    for (int i=1; i<=upto; i++) {
        vector<int> p={1, G[i]%MOD};
        v.push_back(move(p));
    }
    while (v.size()>1) {
        vector<vector<int>> nxt;
        for (int i=0; i<v.size(); i+=2)
            if (i+1==v.size()) {
                if (v[i].size()>k)
                    v[i].resize(k);
                nxt.push_back(move(v[i]));
            }
            else nxt.push_back(NTT<MOD, 3>::conv(v[i], v[i+1], k));
        v.swap(nxt);
    }
    if (v[0].size()>k)
        v[0].resize(k);
    return v[0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<int> G(m+1, 0);
    G[1]=1;
    for (int i=2; i<=m; i++) {
        int t=G[i-1];
        G[i]=1+G[i-G[t]];
    }
    auto poly=product(G, m-1, n);
    int coef=poly[n-1];
    cout << 1LL*G[m]*coef%MOD;
}