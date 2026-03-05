#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

static int inv(int a, int mod) {
    int b=mod, u=1, v=0;
    while (b) {
        int t=a/b;
        a-=t*b; swap(a, b);
        u-=t*v; swap(u, v);
    }
    u%=mod;
    if (u<0) u+=mod;
    return u;
}

bool prime(int n) {
    if (n==2) return true;
    if (n<2 || n%2==0) return false;
    for (int i=3; i*i<=n; i+=2)
        if (n%i==0) return false;
    return true;
}
int divi(int n) {
    for (int i=2; i*i<=n; i++)
        if (n%i==0) return i;
    return -1;
}

int find_t(int p, const vector<bool> &T, int d, int u) {
    int k=inv(d, p);
    int l=u*k%p, r=p;
    while (l+1!=r) {
        int mid=(l+r)/2;
        if (T[mid*d%p]) l=mid;
        else r=mid;
    }
    return r*d%p;
}

static vector<int> egz(int n, const vector<int> &a, const vector<int> &idx);

static vector<int> prime_case(int p, const vector<int> &a, const vector<int> &idx) {
    int m=2*p-1;
    vector<int> ord(m);
    iota(ord.begin(), ord.end(), 0);
    ranges::sort(ord, [&](int i, int j) {
        return a[i]%p<a[j]%p;
    });
    for (int i=0; i<p; i++) if (a[ord[i]]%p==a[ord[i+p-1]]%p) {
        vector<int> r;
        for (int j=i; j<i+p; j++)
            r.push_back(idx[ord[j]]);
        return r;
    }

    vector<bool> use(m), T(p);
    vector<int> P(p, -1);
    int s=0;
    for (int i=0; i<p; i++)
        use[ord[i]]=1, s=(s+a[ord[i]])%p;
    T[s]=1;

    while (!T[0])
        for (int i=1; i<p && !T[0]; i++) {
            int d=(a[ord[i+p-1]]-a[ord[i-1]])%p;
            if (d<0) d+=p;
            int t=find_t(p, T, d, s);
            if (!T[t]) T[t]=1, P[t]=i;
        }

    int c=0;
    while (s!=c) {
        int in=ord[P[c]+p-1], out=ord[P[c]-1];
        use[in]=1;
        use[out]=0;
        int d=(a[in]-a[out])%p;
        if (d<0) d+=p;
        c=(c-d)%p;
        if (c<0) c+=p;
    }

    vector<int> r;
    for (int i=0; i<m; i++)
        if (use[i]) r.push_back(idx[i]);
    return r;
}

static vector<int> comp_case(int p, int q, const vector<int> &a, const vector<int> &idx) {
    int n=p*q;
    vector<int> pool;
    for (int i=0; i<p-1; i++) pool.push_back(i);
    int ptr=p-1;

    vector<vector<int>> grid(q*2-1);
    vector<int> v(q*2-1);

    for (int i=0; i<q*2-1; i++) {
        for (int k=0; k<p; k++) pool.push_back(ptr+k);
        ptr+=p;
        vector<int> sub(p*2-1), sid(2*p-1);
        for (int k=0; k<p*2-1; k++)
            sub[k]=a[pool[k]], sid[k]=idx[pool[k]];
        auto pick=egz(p, sub, sid);
        ranges::sort(pick);
        vector<bool> mark(p*2-1);
        for (int k=0; k<p*2-1; k++)
            mark[k]=ranges::binary_search(pick, sid[k]);
        vector<int> new_pool;
        int s=0;
        for (int k=0; k<p*2-1; k++)
            if (mark[k])
                grid[i].push_back(sid[k]), s+=sub[k];
            else new_pool.push_back(pool[k]);
        pool.swap(new_pool);
        v[i]=s/p;
    }

    vector<int> ord(2*q-1);
    iota(ord.begin(), ord.end(), 0);
    auto choose=egz(q, v, ord);
    vector<int> r;
    for (int g: choose)
        for (int x: grid[g])
            r.push_back(x);
    return r;
}

static vector<int> egz(int n, const vector<int>&a, const vector<int>&idx) {
    if (n==1) return {idx[0]};
    if (prime(n)) return prime_case(n, a, idx);
    int p=divi(n);
    return comp_case(p, n/p, a, idx);
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n*2-1), idx(n*2-1);
    for (auto &x: a) cin >> x;
    iota(idx.begin(), idx.end(), 0);
    auto r=egz(n, a, idx);
    for (int i=0; i<n; i++)
        cout << a[r[i]] << ' ';
    cout << '\n';
}