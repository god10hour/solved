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
        v.resize(s); ntt(v, false);
        u.resize(s); ntt(u, false);
        for (int i=0; i<s; i++)
            v[i]=1LL*v[i]*u[i]%mod;
        ntt(v, true),  v.resize(n);
        return v;
    }
};

struct CRT {
    static constexpr int m0=998244353;
    static constexpr int m1=469762049;
    static constexpr int m2=1224736769;
    static constexpr int G=3;

    NTT<m0, G> P0;
    NTT<m1, G> P1;
    NTT<m2, G> P2;

    int inv01, inv012;
    int mm_m2;

    CRT() {
        inv01=pow(m0%m1, m1-2, m1);
        mm_m2=1LL*m0*m1%m2;
        inv012=pow(mm_m2, m2-2, m2);
    }

    static int pow(int n, int k, int mod) {
        int r=1;
        while (k) {
            if (k&1) r=1LL*r*n%mod;
            n=1LL*n*n%mod;
            k>>=1;
        }
        return r;
    }

    int combine_mod_p(int a0, int a1, int a2, int p) const {
        int64_t t1=a1-a0;
        if (t1<0) t1+=m1;
        t1=t1*inv01%m1;

        int64_t t2=a2-(a0+1LL*(m0%m2)*t1)%m2;
        if (t2<0) t2+=m2;
        t2=t2*inv012%m2;

        return (a0
            +1LL*(m0%p)*(t1%p)
            +1LL*(1LL*m0*m1%p)*(t2%p))%p;
    }

    vector<int> conv(const vector<int> &V, const vector<int> &U, int p) {
        if (V.empty() || U.empty()) return {};
        int n=V.size()+U.size()-1;
        array<vector<int>, 3> v, u;
        for (int i=0; i<3; i++) v[i].resize(V.size());
        for (int i=0; i<3; i++) u[i].resize(U.size());

        for (int i=0; i<(int)V.size(); i++) {
            int x=V[i];
            v[0][i]=x%m0; if (v[0][i]<0) v[0][i]+=m0;
            v[1][i]=x%m1; if (v[1][i]<0) v[1][i]+=m1;
            v[2][i]=x%m2; if (v[2][i]<0) v[2][i]+=m2;
        }
        for (int i=0; i<(int)U.size(); i++) {
            int x=U[i];
            u[0][i]=x%m0; if (u[0][i]<0) u[0][i]+=m0;
            u[1][i]=x%m1; if (u[1][i]<0) u[1][i]+=m1;
            u[2][i]=x%m2; if (u[2][i]<0) u[2][i]+=m2;
        }

        auto w0=P0.conv(v[0], u[0]);
        auto w1=P1.conv(v[1], u[1]);
        auto w2=P2.conv(v[2], u[2]);

        vector<int> r(n);
        int64_t m0m1=1LL*m0*m1%p;
        for (int i=0; i<n; i++) {
            int a0=w0[i], a1=w1[i], a2=w2[i];

            int64_t t1=a1-a0;
            if (t1<0) t1+=m1;
            t1=t1*inv01%m1;

            int64_t x_mod_m2=(a0+1LL*(m0%m2)*t1)%m2;
            int64_t t2=a2-x_mod_m2;
            if (t2<0) t2+=m2;
            t2=t2*inv012%m2;

            r[i]=(a0
                +1LL*(m0%p)*(t1%p)
                +1LL*m0*(m1%p)*(t2%p))%p;
        }
        return r;
    }
};

constexpr int mod=1e9+7;
int p;
CRT crt;

string strip_zero(const string &s) {
    int i=0;
    while (i+1<s.size() && s[i]=='0') i++;
    return s.substr(i);
}

pair<string, int> div_mod(const string &s, int p) {
    string q;
    int rem=0;
    for (char c: s) {
        int cur=rem*10+(c-'0'), d=cur/p;
        rem=cur%p;
        if (!q.empty() || d) q.push_back(char('0'+d));
    }
    if (q.empty()) q="0";
    return {q, rem};
}

string inc_dec(string s) {
    for (int i=s.size()-1; i>=0; i--) {
        if (s[i]<'9') {
            s[i]++;
            return s;
        }
        s[i]='0';
    }
    return "1"+s;
}

int lucas(string s, int p) {
    int c=1;
    s=strip_zero(s);
    while (s.size()!=1 || s[0]!='0') {
        auto [q, r]=div_mod(s, p);
        c=1LL*c*(r+1)%mod;
        s=strip_zero(q);
    }
    return c;
}

vector<int> prod_range(int l, int r) {
    if (l>r) return {1};
    if (l==r) return {1, l};
    int mid=(l+r)/2;
    auto L=prod_range(l, mid);
    auto R=prod_range(mid+1, r);
    return crt.conv(L, R, p);
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    string n;
    cin >> n >> p;
    auto [a, b]=div_mod(n, p);
    if (b==p-1) a=inc_dec(a), b=0;

    int left=lucas(a, p);
    auto poly=prod_range(1, b);
    int right=0;
    for (int x: poly) right+=x!=0;
    cout << 1LL*left*right%mod << '\n';
}