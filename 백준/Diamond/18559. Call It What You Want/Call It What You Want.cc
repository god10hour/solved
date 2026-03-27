#include <bits/stdc++.h>
using namespace std;
constexpr int N=1e5+1;

vector<int> prime;
vector<vector<int>> poly_cache(N);
array<int, N> spf, phi;
array<char, N> mu;

void sieve() {
    phi[1]=mu[1]=1;
    for (int i=2; i<N; i++) {
        if (!spf[i]) {
            spf[i]=i;
            prime.emplace_back(i);
            phi[i]=i-1;
            mu[i]=-1;
        }
        for (int &p: prime) {
            if (1LL*i*p>=N) break;
            spf[p*i]=p;
            if (i%p==0) {
                phi[p*i]=p*phi[i];
                mu[p*i]=0;
                break;
            }
            phi[p*i]=phi[i]*(p-1);
            mu[p*i]=-mu[i];
        }
    }
}

vector<int> factorize(int n) {
    vector<int> ps;
    while (n>1) {
        int p=spf[n];
        ps.emplace_back(p);
        while (n%p==0) n/=p;
    }
    return ps;
} // distinct primes
vector<pair<int, int>> factorize_full(int n) {
    vector<pair<int, int>> ps;
    while (n>1) {
        int p=spf[n], e=0;
        while (n%p==0) n/=p, e++;
        ps.emplace_back(p, e);
    }
    return ps;
}

void enum_divisors(
        int idx, int cur,
        const vector<pair<int, int>> &fac,
        vector<int> &divs
    ) {
    if (idx==fac.size()) {
        divs.emplace_back(cur);
        return;
    }

    auto [p, e]=fac[idx];
    int v=1;
    for (int i=0; i<=e; i++) {
        enum_divisors(idx+1, cur*v, fac, divs);
        v*=p;
    }
}

const vector<int> &get_poly(int n) {
    if (!poly_cache[n].empty()) return poly_cache[n];
    if (n==1) return poly_cache[1]={-1, 1};

    int deg=phi[n];
    vector<int> A(deg+1);
    A[0]=1;
    vector<int> ps=factorize(n);
    int m=ps.size();

    for (int k=0; k<(1<<m); k++) {
        int s=1, bits=0;
        for (int i=0; i<m; i++) if (k>>i&1) {
            s*=ps[i];
            bits++;
        }
        int u=n/s;
        if (u>deg) continue;

        if (bits&1)
            for (int i=u; i<=deg; i++) A[i]+=A[i-u];
        else
            for (int i=deg; i>=u; i--) A[i]-=A[i-u];
    }
    return poly_cache[n]=move(A);
}

string to_string(const vector<int> &A) {
    string s;
    int deg=A.size()-1;
    bool first=true;
    for (int i=deg; i>=0; i--) {
        int c=A[i], v=abs(A[i]);
        if (c==0) continue;
        if (first) {
            if (c<0) s+='-';
            first=false;
        } else s+=c<0? '-': '+';
        if (i==0)
            s+=to_string(v);
        else {
            if (v!=1) s+=to_string(v);
            s+='x';
            if (i>=2) s+='^'+to_string(i);
        }
    }
    return s;
}

bool by_order(int x, int y) {
    const auto &A=get_poly(x);
    const auto &B=get_poly(y);
    int a=A.size()-1, b=B.size()-1;
    if (a!=b) return a<b;
    for (int i=a; i>=0; i--)
        if (A[i]!=B[i])
            return A[i]<B[i];
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    sieve();
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        auto fac=factorize_full(n);
        vector<int> divs;
        enum_divisors(0, 1, fac, divs);
        ranges::sort(divs, by_order);
        string r;
        for (int &x: divs) {
            r+='(';
            r+=to_string(get_poly(x));
            r+=')';
        }
        cout << r << '\n';
    }
}