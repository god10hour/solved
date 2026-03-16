#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr lint mod=998244353;
constexpr int    N=1e6+1;

array<lint, N> roll, p;
lint get(int l, int r) {
    lint rs=roll[r]-roll[l];
    if (rs<0) rs+=mod;
    (rs*=p[N-r])%=mod;
    return rs;
}

int run(const string &s) {
    int n=s.size();
    for (int i=1; i<=n; i++) (roll[i]=roll[i-1]*31+s[i-1])%=mod;
    for (int i=1; i<=n; i++) {
        if (n%i) continue;
        bool z=true;
        for (int j=i*2; j<=n; j+=i)
            if (get(j-i, j)!=get(j-i*2, j-i)) {
                z=false;
                break;
            }
        if (z) return n/i;
    }
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    p[0]=1;
    for (int i=1; i<N; i++) p[i]=p[i-1]*31%mod;
    while (1) {
        string s;
        cin >> s;
        if (s==".") return 0;
        cout << run(s) << '\n';
    }
}