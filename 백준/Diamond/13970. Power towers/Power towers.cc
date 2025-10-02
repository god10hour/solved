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
    if (i>=x.size()) return 1.0>=THRESH;
    long double a=x[i];
    if (a<=1.0L) return a>=THRESH;
    return tower(x, i+1, ceil(log(THRESH)/log(a)));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    const int MAX=1<<20;
    vector<int> phi(MAX);
    iota(phi.begin(), phi.end(), 0);
    for (int i=2; i<MAX; i++) if (i==phi[i])
        for (int j=i; j<MAX; j+=i)
            phi[j]-=phi[j]/i;
    int t, n, M;
    vector<int> x;

    function<int(int, int)> f=[&](int i, int m) {
        if (m==1) return 0;
        if (i==n-1) return x[i]%m;
        int e=f(i+1, phi[m]);
        if (tower(x, i+1, phi[m])) e+=phi[m];
        return Pow(x[i], e, m);
    };
    cin >> t >> M;
    while (t--) {
        cin >> n;
        x.resize(n);
        for (int i=0; i<n; i++)
            cin >> x[i];
        cout << f(0, M) << '\n';
    }
}