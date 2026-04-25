#include <bits/stdc++.h>
using namespace std;
constexpr int inf=1e9;

struct Perm {
    int n=0;
    vector<int> a, init;

    Perm()=default;
    explicit Perm(vector<int> a): n(a.size()), a(a) {
        init.assign(n+1,0);
        for (int i=1; i<=n; i++)
            init[i]=a[i-1];
    }

    int cost(int rot) const {
        int L=n+1, r=0;
        vector<int> to(L), vis(L);
        for (int x=0; x<L; x++) {
            int p=x-rot;
            if (p<0) p+=L;
            to[x]=init[p];
        }

        for (int i=0; i<L; i++) {
            if (vis[i]) continue;
            int x=i, sz=0;
            bool z=false;
            while (!vis[x]) {
                vis[x]=1;
                sz++;
                if (x==0) z=true;
                x=to[x];
            }
            if (sz>1) r+=z? sz-1: sz+1;
        }
        return r;
    }

    pair<int, int> min_case(int par) const {
        pair r(inf, -1);
        for (int i=0; i<=n; i++) {
            int c=cost(i);
            if (c%2==par && c<r.first)
                r={c, i};
        }
        return r;
    }

    vector<int> labels(int rot) const {
        int L=n+1;
        vector<int> to(L), vis(L), labels;
        vector<vector<int>> cyc;

        for (int x=0; x<L; x++) {
            int p=x-rot;
            if (p<0) p+=L;
            to[x]=init[p];
        }
        for (int i=0; i<L; i++) {
            if (vis[i]) continue;
            vector<int> v;
            int x=i;
            while (!vis[x]) {
                vis[x]=1;
                v.emplace_back(x);
                x=to[x];
            }
            if (v.size()>1) cyc.emplace_back(v);
        }

        for (auto &v: cyc) {
            auto it=ranges::find(v, 0);
            if (it==v.end()) continue;
            ranges::rotate(v, it);
            for (int i=v.size()-1; i>0; i--)
                labels.emplace_back(v[i]);
        }
        for (auto &v: cyc) {
            if (auto it=ranges::find(v, 0); it!=v.end()) continue;
            labels.emplace_back(v[0]);
            for (int i=v.size()-1; i>0; i--)
                labels.emplace_back(v[i]);
            labels.emplace_back(v[0]);
        }
        return labels;
    }

    vector<int> make_ops(int par) const {
        auto [c, rot]=min_case(par);
        vector<int> lbs=labels(rot), cur=a, ops;
        for (int x: lbs) {
            int pos=ranges::find(cur, x)-cur.begin();
            ops.emplace_back(pos+1);
            vector<int> nxt;
            nxt.reserve(n);
            for (int i=pos+1; i<n; i++)
                nxt.emplace_back(cur[i]);
            nxt.emplace_back(cur[pos]);
            for (int i=0; i<pos; i++)
                nxt.emplace_back(cur[i]);
            cur.swap(nxt);
        }
        return ops;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;
    Perm A(a), B(b);

    int u=inf, par=-1;
    for (int p=0; p<2; p++) {
        auto ca=A.min_case(p);
        auto cb=B.min_case(p);
        if (ca.first==inf || cb.first==inf) continue;
        int now=max(ca.first, cb.first);
        if (now<u) {
            u=now;
            par=p;
        }
    }
    if (par==-1) return !(cout << -1 << '\n');

    vector<int> oa=A.make_ops(par), ob=B.make_ops(par);
    while (oa.size()<u) {
        oa.emplace_back(1);
        oa.emplace_back(n);
    }
    while (ob.size()<u) {
        ob.emplace_back(1);
        ob.emplace_back(m);
    }
    cout << u << '\n';
    for (int i=0; i<u; i++)
        cout << oa[i] << ' ' << ob[i] << '\n';
}