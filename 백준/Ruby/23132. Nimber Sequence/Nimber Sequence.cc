#include <bits/stdc++.h>
using namespace std;
using u16=uint16_t;
using u32=uint32_t;
using u64=uint64_t;

namespace nim {
    constexpr u16 G16=10279U;
    u16 expBuffer[4*(1<<16)+4];
    u16 *exp=expBuffer+(2*(1<<16)+4), *exp3=exp+3, *exp6=exp+6;
    int log[1<<16];

    template<int L>
    inline u64 mulSlow(u64 a, u64 b) {
        static constexpr int l=L>>1;
        const u64 a0=a&((1ULL<<l)-1), a1=a>>l;
        const u64 b0=b&((1ULL<<l)-1), b1=b>>l;
        const u64 a0b0=mulSlow<l>(a0, b0);
        return (a0b0^mulSlow<l>(1ULL<<(l-1), mulSlow<l>(a1, b1)))
               |(a0b0^mulSlow<l>(a0^a1, b0^b1))<<l;
    }

    template<>
    inline u64 mulSlow<1>(u64 a, u64 b) { return a&b; }

    inline u32 mul31(u32 a) {
        const u16 a0=a, a1=a>>16;
        const u16 a01=a0^a1;
        return exp6[log[a1]]|(u32)exp3[log[a01]]<<16;
    }

    inline u16 mul(u16 a, u16 b) {
        return exp[log[a]+log[b]];
    }

    inline u32 mul(u32 a, u32 b) {
        const u16 a0=a, a1=a>>16;
        const u16 b0=b, b1=b>>16;
        const u16 a01=a0^a1;
        const u16 b01=b0^b1;
        const u16 a0b0=mul(a0, b0);
        return (a0b0^exp3[log[a1]+log[b1]])|(u32)(a0b0^mul(a01, b01))<<16;
    }

    inline u64 mul(u64 a, u64 b) {
        const u32 a0=a, a1=a>>32;
        const u32 b0=b, b1=b>>32;
        const u32 a01=a0^a1;
        const u32 b01=b0^b1;
        const u32 a0b0=mul(a0, b0);
        return (a0b0^mul31(mul(a1, b1)))|(u64)(a0b0^mul(a01, b01))<<32;
    }

    struct Preparator {
        Preparator() {
            exp[0]=1;
            for (int i=1; i<(1<<16)-1; ++i)
                exp[i]=mulSlow<16>(exp[i-1], G16);
            for (int i=(1<<16)-1; i<2*(1<<16); ++i)
                exp[i]=exp[i-((1<<16)-1)];
            for (int i=0; i<(1<<16)-1; ++i)
                log[exp[i]]=i;
            log[0]=-(1<<16)-2;
        }
    } preparator;
}  // namespace nim

int64_t k, m;
vector<u32> f, g;
vector<u32> v;
u32 x;

vector<u32> small(vector<u32> &a, vector<u32> &b) {
    vector<u32> r(a.size()+b.size()-1, 0);
    for (int i=0; i<a.size(); i++)
        for (int j=0; j<b.size(); j++)
            r[i+j]^=nim::mul(a[i], b[j]);
    return r;
}

vector<u32> fANDg(vector<u32> &P, vector<u32> &F, vector<u32> &G) {
    vector<u32> v=small(P, F);
    vector<u32> u=small(P, G);
    v.resize(P.size()+k-1);
    for (int i=0; i<u.size(); i++)
        v[i+k-5]^=u[i];
    return v;
}

u32 bostanMori(vector<u32> &p, int64_t n) {
    vector<u32> P=p, F=f, G=g;
    while (n) {
        vector<u32> u=fANDg(P, F, G);
        vector<u32> ff=small(F, F);
        vector<u32> gg=small(G, G);
        F.clear(), G.clear();
        for (int i=0; i<ff.size(); i++)
            if ((i&1)==0)
                F.push_back(ff[i]);
        for (int i=0; i<gg.size(); i++)
            if ((i&1)==0)
                G.push_back(gg[i]);

        vector<u32> t;
        for (int i=0; i<u.size(); i++)
            if ((i&1)==(n&1))
                t.push_back(u[i]);
        P=move(t);
        n/=2;
    }
    return P[0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> k >> m;
    m--;

    f.push_back(1);
    for (int i=0; i<k-1; i++) {
        cin >> x;
        v.push_back(x);
    }
    for (int i=0; i<5; i++) {
        cin >> x;
        f.push_back(x);
    }
    g.resize(5);
    for (int i=4; i>=0; i--) {
        cin >> x;
        g[i]=x;
    }

    vector<u32> p=fANDg(v, f, g);
    p.resize(k-1);

    cout << bostanMori(p, m);
}