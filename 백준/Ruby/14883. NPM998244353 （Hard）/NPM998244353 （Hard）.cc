#include <bits/stdc++.h>
using namespace std;

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
        const int s=v.size();
        for (int i=1, j=0; i<s; i++) {
            int bit=s>>1;
            while (!((j^=bit)&bit)) bit>>=1;
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

using lint=int64_t;
constexpr int MOD=998244353;
constexpr int ROOT=3;
NTT<MOD, ROOT> ntt;
int lim;

vector<int> conv(const vector<int> &v, const vector<int> &u) {
    auto w=ntt.conv(v, u);
    if (w.size()>lim+1) w.resize(lim+1);
    while (!w.empty() && w.back()==0) w.pop_back();
    return w;
}

vector<vector<int>> build(const vector<int> &base, lint N) {
    vector<vector<int>> P;
    if (N<=0) return P;
    vector<int> b=base;
    while (!b.empty() && b.back()==0) b.pop_back();
    P.push_back(b);

    lint bit=1;
    while (bit<<1<=N) {
        vector<int> nxt=conv(P.back(), P.back());
        P.push_back(move(nxt));
        bit<<=1;
    }
    return P;
}

vector<int> pow(lint n, const vector<vector<int>> &base) {
    vector r(1, 1);
    int k=0;
    while (n>0) {
        if (n&1) r=conv(r, base[k]);
        n>>=1;
        k++;
    }
    return r;
}

vector<lint> residues(int n, int p) {
    vector<lint> cnt(p, 0);
    if (p==1) {
        cnt[0]=n;
        return cnt;
    }
    vector<int> first(p, -1), seq;
    seq.reserve(p+5);
    int c=1;
    lint pos=0;

    while (true) {
        if (pos==n) {
            for (int i=0; i<n; i++)
                cnt[seq[i]]++;
            break;
        }
        if (first[c]!=-1) {
            int s=first[c];
            int len=pos-s, plen=s;
            int tot=n, use=min(tot, plen);
            for (int i=0; i<use; i++) cnt[seq[i]]++;

            if (tot>plen) {
                int rem=tot-plen;
                for (int i=0; i<len; i++)
                    cnt[seq[s+i]]+=rem/len;
                for (int i=0; i<rem%len; i++)
                    cnt[seq[s+i]]++;
            }
            break;
        }
        first[c]=pos;
        seq.push_back(c);
        c=c*10%p;
        pos++;
    }
    return cnt;
}

vector<vector<int>> group(
    const vector<vector<int>> &A,
    const vector<vector<int>> &B,
    int P
) {
    vector<vector<int>> C(P);
    for (int i=0; i<P; i++) {
        if (A[i].empty()) continue;
        for (int j=0; j<P; j++) {
            if (B[j].empty()) continue;
            int r=i+j;
            if (r>=P) r-=P;
            auto z=conv(A[i], B[j]);
            if (z.empty()) continue;
            if (C[r].size()<z.size()) C[r].resize(z.size(), 0);
            for (int k=0; k<z.size(); k++) {
                int x=C[r][k]+z[k];
                if (x>=MOD) x-=MOD;
                C[r][k]=x;
            }
        }
    }
    return C;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, p, MM;
    cin >> n >> p >> MM;
    lim=MM;

    vector base(lim+1, 0);
    int D=min(9, lim);
    for (int d=0; d<=D; d++) base[d]=1;

    if (p==1) {
        auto S=pow(n, build(base, n));
        vector exact(lim+1, 0), pref(lim+1, 0);
        for (int i=0; i<=lim && i<S.size(); i++)
            exact[i]=S[i];
        int c=0;
        for (int i=0; i<=lim; i++) {
            c+=exact[i];
            if (c>=MOD) c-=MOD;
            pref[i]=c;
        }
        for (int i=0; i<=lim; i++)
            cout << pref[i] << ' ';
        return 0;
    }

    auto cnt=residues(n, p);
    lint N=0;
    for (int c=0; c<p; c++)
        if (cnt[c]>N)
            N=cnt[c];

    auto P=build(base, N);
    vector<int> resi;
    for (int i=1; i<p; i++)
        if (cnt[i]>0)
            resi.push_back(i);
    lint n0=cnt[0];
    vector<vector<int>> F(p);
    F[0].push_back(1);

    for (int c: resi) {
        vector<int> s_c=pow(cnt[c], P);

        vector<vector<int>> G(p);
        int len=min<int>(s_c.size(), lim+1);
        for (int k=0; k<len; k++) {
            int coef=s_c[k];
            if (!coef) continue;
            int r=1LL*c*k%p;
            if (G[r].size()<=k) G[r].resize(k+1, 0);
            int x=G[r][k]+coef;
            if (x>=MOD) x-=MOD;
            G[r][k]=x;
        }
        F=group(F, G, p);
    }

    if (n0>0) {
        vector<int> S0=pow(n0, P);
        for (int i=0; i<p; i++) {
            if (F[i].empty())
                continue;
            F[i]=conv(F[i], S0);
        }
    }

    vector exact(lim+1, 0);
    if (!F[0].empty()) {
        int len=min<int>(F[0].size(), lim+1);
        for (int i=0; i<len; i++)
            exact[i]=F[0][i];
    }

    vector pref(lim+1, 0);
    int c=0;
    for (int i=0; i<=lim; i++) {
        c+=exact[i];
        if (c>=MOD) c-=MOD;
        pref[i]=c;
    }
    for (int i=0; i<=lim; i++)
        cout << pref[i] << ' ';
}