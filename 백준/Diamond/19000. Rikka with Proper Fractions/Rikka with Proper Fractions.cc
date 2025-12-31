#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

constexpr int N=4000000+50;
constexpr int MOD=998244353;

int mu[N];
bool mark[N];
vector<int> prime;
lint M[N];
unordered_map<lint, lint> memo;

void sieve() {
    mu[1]=1;
    for (int i=2; i<N; i++) {
        if (!mark[i]) {
            prime.push_back(i);
            mu[i]=-1;
        }
        for (int p: prime) {
            lint x=1LL*i*p;
            if (x>=N) break;
            mark[x]=1;
            if (i%p==0) break;
            mu[x]=-mu[i];
        }
    }
    for (int i=1; i<N; i++) M[i]=M[i-1]+mu[i];
}

lint sum_mu(lint n) {
    if (n<N) return M[n];
    auto it=memo.find(n);
    if (it!=memo.end()) return it->second;
    lint r=1;
    for (lint i=2, j; i<=n; i=j+1) {
        j=n/(n/i);
        r-=(j-i+1)*sum_mu(n/i);
    }
    return memo[n]=r;
}

lint floor_sum(lint n, lint m, lint a, lint b=0) {
    __int128 r=0;
    while (1) {
        if (a>=m) r+=__int128(n)*(n-1)*(a/m)/2, a%=m;
        if (b>=m) r+=__int128(n)*(b/m), b%=m;
        __int128 y=__int128(a)*n+b;
        if (y<m) break;
        n=y/m, b=y%m;
        swap(m, a);
    }
    return r%MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    sieve();
    int t;
    cin >> t;
    while (t--) {
        lint n, a, b, c, d;
        cin >> n >> a >> b >> c >> d;
        auto f=[&](lint x)->lint {
            x=max<lint>(x, 0);
            return floor_sum(x, d, c, c)-floor_sum(x, b, a, a-1);
        };

        lint rs=0;
        for (lint l=1, r; l<=n; l=r+1) {
            r=n/(n/l);
            lint coef=sum_mu(r)-sum_mu(l-1);
            (rs+=coef*f(n/l))%=MOD;
            if (rs<0) rs+=MOD;
        }
        cout << rs << '\n';
    }
}