#include <bits/stdc++.h>
using namespace std;
using Row=uint32_t;
const int MOD=998244353;

int64_t power(int64_t n, int64_t k) {
    int64_t r=1;
    while (k) {
        if (k&1)
            r=r*n%MOD;
        n=n*n%MOD;
        k>>=1;
    }
    return r;
}

// Rank over GF(2) 
int grank(vector<Row> a, int n) {
    int R=a.size(), r=0;
    for (int c=n-1; c>=0 && r<R; c--) {
        int piv=-1;
        for (int i=r; i<R; i++)
            if (a[i]>>c&1) {
                piv=i;
                break;
            }
        if (piv==-1) continue;
        if (piv!=r) swap(a[r], a[piv]);
        for (int i=0; i<R; i++)
            if (i!=r && a[i]>>c&1)
                a[i]^=a[r];
        r++;
    }
    return r;
}

// Kernel
vector<Row> nullspace(const vector<Row> &M, int col) {
    int R=M.size();
    vector<Row> A=M;
    vector<int> pivot(R, -1);
    int r=0;
    for (int c=col-1; c>=0 && r<R; c--) {
        int piv=-1;
        for (int i=r; i<R; i++)
            if (A[i]>>c&1) {
                piv=i;
                break;
            }
        if (piv==-1) continue;
        swap(A[r], A[piv]);
        for (int i=0; i<R; i++)
            if (i!=r && A[i]>>c&1)
                A[i]^=A[r];
        pivot[r]=c;
        r++;
    }
    vector<bool> isPivot(col, 0);
    for (int i=0; i<r; i++)
        if (pivot[i]!=-1)
            isPivot[pivot[i]]=1;
    vector<Row> basis;
    for (int f=0; f<col; f++)
        if (!isPivot[f]) {
            Row v=Row(1)<<f;
            for (int i=0; i<r; i++) {
                int c=pivot[i];
                Row row=A[i]&~(Row(1)<<c);
                int sum=__builtin_popcount(row&v)&1;
                if (sum) v^=Row(1)<<c;
            }
            basis.push_back(v);
        }
    return basis;
}

void fwt(vector<int64_t> &a, bool inv) {
    int n=a.size();
    for (int k=1; k*2<=n; k*=2)
        for (int i=0; i<n; i+=k*2)
            for (int j=0; j<k; j++) {
                int64_t u=a[i+j], v=a[i+j+k];
                a[i+j]=u+v;
                a[i+j+k]=u-v;
            }
    if (inv)
        for (int i=0; i<n; i++)
            a[i]/=n;
}

struct TSpace {
    int n, dim;
    vector<Row> Trow;
    vector<Row> Qrow;
};

TSpace buildTQ(int n, const string &bits) {
    int S=1<<n;
    vector<int64_t> s(S);
    for (int x=0; x<S; x++)
        s[x]=bits[x]-'0'? -1:1;
    vector<int64_t> A=s;
    fwt(A, 0);
    for (int i=0; i<S; i++)
        A[i]=A[i]*A[i];
    fwt(A, 1);
    vector<Row> Ts;
    for (int i=0; i<S; i++)
        if (A[i]==(1LL<<n))
            Ts.push_back(i);

    vector<Row> T;
    vector<Row> t=Ts;
    for (Row v: t) {
        Row w=v;
        for (int b=n-1; b>=0; b--) {
            if (!(w>>b&1)) continue;
            for (Row u: T)
                if (u>>b&1)
                    w^=u;
            if (!(w>>b&1)) continue;
            T.push_back(w);
            break;
        }
    }
    int d=T.size();
    vector<Row> Q=nullspace(T, n);
    TSpace r={n, d, T, Q};
    return r;
}

using Perm=vector<int>;
Perm read(int n) {
    Perm p(n);
    for (int i=0; i<n; i++) {
        int x;
        cin >> x;
        p[i]=--x;
    }
    return p;
}
Perm compose(const Perm &a, const Perm &b) {
    int n=a.size();
    Perm c(n);
    for (int i=0; i<n; i++)
        c[i]=a[b[i]];
    return c;
}
Perm power(Perm p, int64_t k) {
    int n=p.size();
    vector<int> vis(n, 0), out(n);
    for (int i=0; i<n; i++)
        if (!vis[i]) {
            vector<int> cyc;
            int u=i;
            while (!vis[u]) {
                vis[u]=1;
                cyc.push_back(u);
                u=p[u];
            }
            int c=cyc.size();
            int64_t r=k%c;
            for (int j=0; j<c; ++j)
                out[cyc[j]]=cyc[(j+r)%c];
        }
    return out;
}

struct MatGF2 {
    int n;
    vector<Row> cols;
};

MatGF2 buildLk(const Perm &p, int64_t k) {
    int n=p.size();
    vector<int> cid(n, -1), pos(n, -1);
    vector<vector<int>> cycle;
    int cc=0;
    for (int i=0; i<n; i++)
        if (cid[i]<0) {
            vector<int> cyc;
            int u=i;
            while (cid[u]<0) {
                cid[u]=cc;
                pos[u]=cyc.size();
                cyc.push_back(u);
                u=p[u];
            }
            cycle.push_back(move(cyc));
            cc++;
        }
    MatGF2 L={n, vector<Row>(n, 0)};

    for (int i=0; i<n; i++) {
        const auto &cyc=cycle[cid[i]];
        int c=cyc.size();
        int64_t q=k/c;
        int r=k%c;
        Row col=0;
        if (q&1LL)
            for (int node: cyc)
                col|=(Row(1)<<node);
        int s=pos[i];
        for (int j=0; j<r; j++)
            col^=Row(1)<<cyc[(s+j)%c];
        L.cols[i]=col;
    }
    return L;
}

// Q * L
vector<Row> QL(const vector<Row>& Qrow, const MatGF2 &L) {
    int R=Qrow.size();
    int n=L.n;
    vector<Row> A(R, 0);
    for (int i=0; i<n; i++) {
        Row col=L.cols[i];
        for (int r=0; r<R; r++) {
            int bit=__builtin_popcount(Qrow[r]&col)&1;
            if (bit)
                A[r]^=(Row(1)<<i);
        }
    }
    return A; // R * N
}

struct PGroup {
    int N;
    vector<Perm> gens;
    vector<int> base;
    vector<vector<int>> orbit, parent, lab, repr;
    vector<vector<Perm>> strong, Glev;

    explicit PGroup(int N=0): N(N) {}

    void add(const Perm& g) { gens.push_back(g); }

    static Perm compose(const Perm &a, const Perm &b) {
        int n=a.size();
        Perm c(n);
        for (int i=0; i<n; i++)
            c[i]=a[b[i]];
        return c;
    }
    static Perm inv(const Perm &a) {
        int n=a.size();
        Perm r(n);
        for (int i=0; i<n; i++)
            r[a[i]]=i;
        return r;
    }
    static bool identity(const Perm &a) {
        for (int i=0; i<a.size(); i++)
            if (a[i]!=i)
                return 0;
        return 1;
    }
    static int act(const Perm &g, int x) { return g[x]; }

    void rebuild(int Lv) {
        if (Glev.size()!=strong.size())
            Glev.assign(strong.size(), {});
        int L=Glev.size();
        for (int i=Lv; i<L; i++) {
            vector<Perm> P;
            for (int j=i; j<L; j++)
                P.insert(P.end(), strong[j].begin(), strong[j].end());
            Glev[i]=move(P);
        }
    }

    void buildOrb(int Lv) {
        int b=base[Lv];
        orbit[Lv].clear();
        parent[Lv].assign(N, -1);
        lab[Lv].assign(N, -1);
        repr[Lv].assign(N, -1);

        deque<int> dq;
        orbit[Lv].push_back(b);
        repr[Lv][b]=0;
        dq.push_back(b);
        const auto &Guse=Glev[Lv];

        while (!dq.empty()) {
            int u=dq.front();
            dq.pop_front();
            for (int g=0; g<Guse.size(); g++) {
                int v=Guse[g][u];
                if (repr[Lv][v]==-1) {
                    repr[Lv][v]=orbit[Lv].size();
                    orbit[Lv].push_back(v);
                    parent[Lv][v]=u;
                    lab[Lv][v]=g;
                    dq.push_back(v);
                }
            }
        }
    }

    Perm trans(int Lv, int x) const {
        if (repr[Lv][x]==-1) {
            Perm id(N);
            iota(id.begin(), id.end(), 0);
            return id;
        }
        vector<int> path;
        int now=x;
        while (now!=base[Lv]) {
            path.push_back(lab[Lv][now]);
            now=parent[Lv][now];
        }
        Perm t(N);
        iota(t.begin(), t.end(), 0);
        for (int i=path.size()-1; i>=0; i--)
            t=compose(Glev[Lv][path[i]], t);
        return t;
    }

    Perm sift(const Perm &g) {
        Perm h=g;
        for (int Lv=0; Lv<base.size(); Lv++) {
            int b=base[Lv];
            int y=act(h, b);
            if (repr[Lv][y]==-1)
                return h;
            Perm t=trans(Lv, y);
            Perm tinv=inv(t);
            h=compose(tinv, h);
        }
        return h;
    }

    void insert(int Lv, const Perm &g) {
        strong[Lv].push_back(g);
        rebuild(0);
        for (int i=0; i<base.size(); i++)
            buildOrb(i);
    }
    void addbase(int bpt) {
        base.push_back(bpt);
        orbit.emplace_back();
        parent.emplace_back(N, -1);
        lab.emplace_back(N, -1);
        repr.emplace_back(N, -1);
        strong.emplace_back();
        Glev.emplace_back();
        rebuild(base.size()-1);
        buildOrb(base.size()-1);
    }
    void init() {
        base.clear();
        orbit.clear();
        parent.clear();
        lab.clear();
        repr.clear();
        strong.clear();
        Glev.clear();
        for (int i=0; i<N; i++)
            addbase(i);
    }

    void build() {
        init();
        deque<Perm> dq;
        for (auto &g: gens)
            dq.push_back(g);
        while (!dq.empty()) {
            Perm a=dq.front();
            dq.pop_front();
            Perm r=sift(a);
            if (!identity(r)) {
                int i=0;
                for (; i<base.size(); i++)
                    if (act(r, base[i])!=base[i])
                        break;
                if (i==base.size())
                    i=base.size()-1;
                insert(i, r);
                for (int u: orbit[i]) {
                    Perm t=trans(i, u);
                    Perm tinv=inv(t);
                    for (auto &s: Glev[i]) {
                        Perm c=compose(compose(tinv, s), t);
                        dq.push_back(c);
                    }
                }
            }
        }
    }

    bool contains(const Perm &x) {
        Perm r=sift(x);
        return identity(r);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    string bits;
    cin >> n >> m >> bits;
    int S=1<<n;

    vector<Perm> sigma;
    sigma.reserve(m);
    for (int i=0; i<m; i++)
        sigma.push_back(read(n));

    TSpace tsp=buildTQ(n, bits);
    bool const_=tsp.dim==n;
    PGroup G(n);
    for (auto &g: sigma)
        G.add(g);
    G.build();

    int Q;
    cin >> Q;
    while (Q--) {
        int64_t k;
        cin >> k;
        Perm pi=read(n);
        if (k==0 || const_) {
            cout << power(2, n) << '\n';
            continue;
        }
        Perm P=power(pi, k);
        if (!G.contains(P)) {
            cout << 0 << '\n';
            continue;
        }
        MatGF2 Lk=buildLk(pi, k);
        vector<Row> A=QL(tsp.Qrow, Lk);
        int r=grank(A, n);
        cout << power(2, n-r) << '\n';
    }
}