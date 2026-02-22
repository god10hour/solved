#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr int lim=5000000;

vector<int> prime;
vector<int8_t> mu, sieve;
vector<lint> pref;
unordered_map<lint, lint> memoM, memoPhi;

lint mertens(lint n) {
    if (n<=lim) return pref[n];
    if (auto it=memoM.find(n); it!=memoM.end()) return it->second;

    lint rs=1;
    for (lint l=2; l<=n; ) {
        lint q=n/l, r=n/q;
        rs-=(r-l+1)*mertens(q);
        l=r+1;
    }
    memoM.emplace(n, rs);
    return rs;
}

lint phi_sum(lint n) {
    if (n<=0) return 0;
    if (auto it=memoPhi.find(n); it!=memoPhi.end()) return it->second;

    __int128 acc=0;
    for (lint l=1; l<=n; ) {
        lint q=n/l, r=n/q;
        lint s=mertens(r)-mertens(l-1);
        __int128 m=q, tri=m*(m+1)/2;
        acc+=__int128(s)*tri;
        l=r+1;
    }
    memoPhi.emplace(n, acc);
    return acc;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    lint L;
    cin >> L;
    mu.assign(lim+1, 0);
    sieve.assign(lim+1, 1);
    pref.assign(lim+1, 0);

    mu[1]=1;
    for (int i=2; i<=lim; i++) {
        if (sieve[i]) prime.push_back(i), mu[i]=-1;
        for (int p: prime) {
            lint v=1LL*p*i;
            if (v>lim) break;
            sieve[v]=0;
            if (i%p==0) { mu[v]=0; break; }
            mu[v]=-mu[i];
        }
    }
    for (int i=1; i<=lim; i++) pref[i]=pref[i-1]+mu[i];

    __int128 phiL=phi_sum(L), even=0;
    for (lint k=L/2; k>0; k/=2) even+=phi_sum(k);
    cout << lint((phiL+even-1)/2) << '\n';
}