#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

template<int mod, int root>
struct NTT {
    static int pow(int n, int k) {
        int r=1;
        while (k) {
            if (k&1) r=1LL*r*n%mod;
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
                    int a=v[i+j], b=1LL*v[i+j+k]*uni%mod;
                    v[i+j]=(a+b)%mod;
                    v[i+j+k]=(a-b+mod)%mod;
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
        v.resize(s); ntt(v, false);
        u.resize(s); ntt(u, false);
        for (int i=0; i<s; i++)
            v[i]=1LL*v[i]*u[i]%mod;
        ntt(v, true), v.resize(n);
        return v;
    }
};

constexpr int mod=998244353;
constexpr int G=3, dig=9;
NTT<mod, G> ntt;
int lim;

vector<int> conv(const vector<int> &v, const vector<int> &u) {
    auto w=ntt.conv(v, u);
    if (w.size()>lim+1) w.resize(lim+1);
    while (!w.empty() && w.back()==0) w.pop_back();
    return w;
}

vector<vector<int>> pow_table(const vector<int> &base, lint n) {
    vector<vector<int>> pows;
    if (n<=0) return pows;

    vector<int> cur=base;
    while (!cur.empty() && cur.back()==0) cur.pop_back();
    pows.push_back(cur);

    while (lint(1)<<pows.size()<=n) {
        auto nxt=conv(pows.back(), pows.back());
        pows.push_back(move(nxt));
    }
    return pows;
}

vector<int> poly_pow(lint n, const vector<vector<int>> &pows) {
    vector r(1, 1);
    int k=0;
    while (n>0) {
        if (n&1) r=conv(r, pows[k]);
        n>>=1, k++;
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
    seq.reserve(p+1);
    int cur=1%p;
    lint pos=0;
    while (true) {
        if (pos==n) {
            for (int i=0; i<n; i++) cnt[seq[i]]++;
            break;
        }
        if (first[cur]!=-1) {
            int sta=first[cur], k=pos-sta;
            lint rem=n-sta;
            for (int i=0; i<sta; i++) cnt[seq[i]]++;
            for (int i=0; i<k; i++) cnt[seq[sta+i]]+=rem/k;
            for (int i=0; i<rem%k; i++) cnt[seq[sta+i]]++;
            break;
        }
        first[cur]=pos;
        seq.push_back(cur);
        cur=1LL*cur*10%p;
        pos++;
    }
    return cnt;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, p;
    cin >> n >> p >> lim;
    vector<int> base(lim+1, 0);
    for (int i=0; i<=min(dig, lim); i++) base[i]=1;
    auto cnt=residues(n, p);
    lint mx=0;
    for (lint x: cnt) mx=max(mx, x);
    auto pows=pow_table(base, mx);
    vector<vector<int>> info(p);
    for (int i=0; i<p; i++) {
        if (cnt[i]==0) continue;
        info[i]=poly_pow(cnt[i], pows);
    }

    vector dp(lim+1, vector(p, 0));
    vector<int> seq(lim+1);
    dp[0][0]=1;

    for (int i=0; i<p; i++) {
        if (info[i].empty()) continue;
        vector<vector<int>> nxt=dp;
        for (int r=0; r<p; r++) {
            int cur=r;
            for (int s=0; s<=lim; s++) {
                seq[s]=dp[s][cur];
                cur+=i;
                if (cur>=p) cur-=p;
            }

            auto res=conv(seq, info[i]);
            if (res.size()<lim+1) res.resize(lim+1, 0);
            cur=r;
            for (int s=0; s<=lim; s++) {
                nxt[s][cur]=res[s];
                cur+=i;
                if (cur>=p) cur-=p;
            }
        }
        dp.swap(nxt);
    }

    int pref=0;
    for (int i=0; i<=lim; i++) {
        pref+=dp[i][0];
        if (pref>=mod) pref-=mod;
        cout << pref << ' ';
    }
}