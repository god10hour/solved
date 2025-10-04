#include <bits/stdc++.h>
using namespace std;

int Pow(int64_t n, int k, const int M) {
    int64_t r=1;
    while (k) {
        if (k&1)
            r=r*n%M;
        n=n*n%M;
        k/=2;
    }
    return r;
}

bool tower(const vector<int> &x, int i, long double THRESH) {
    if (THRESH<=1.0) return 1;
    if (i>=x.size()) return 1.0L>=THRESH;
    long double a=x[i];
    if (a<=1.0L) return a>=THRESH;
    return tower(x, i+1, ceil(logl(THRESH)/logl(a)));
}

struct Hash {
    size_t operator()(uint64_t x) const noexcept {
        x+=0x9e3779b97f4a7c15ULL;
        x=(x^x>>30)*0xbf58476d1ce4e5b9ULL;
        x=(x^x>>27)*0x94d049bb133111ebULL;
        return (x^(x>>31));
    }
};
unordered_map<int, int, Hash> mem;
int phi(int x) {
    if (auto it=mem.find(x); it!=mem.end())
        return it->second;
    int r=x, n=x;
    if (x%2==0) {
        r-=r/2;
        while (x%2==0) x/=2;
    }
    for (int i=3; i*i<=x; i+=2)
        if (x%i==0) {
            r-=r/i;
            while (x%i==0) x/=i;
        }
    if (x>1) r-=r/x;
    return mem.emplace(n, r).first->second;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    vector<int> x;

    function<int(int, int)> f=[&](int i, int mod) {
        if (mod==1) return 0;
        if (i==x.size()-1) return x[i]%mod;
        int e=f(i+1, phi(mod));
        if (tower(x, i+1, phi(mod))) e+=phi(mod);
        return Pow(x[i], e, mod);
    };
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        x.assign(50, n);
        cout << f(0, m) << '\n';
    }
}