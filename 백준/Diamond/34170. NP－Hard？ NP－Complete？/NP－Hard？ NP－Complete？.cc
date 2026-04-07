#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
using Lint=__int128_t;

lint run(lint n, lint p, lint k) {
    if (k==0) return n+1;

    lint all=n+1;
    vector<lint> dig;
    for (lint x=n; x; x/=p) dig.emplace_back(x%p);
    if (k>dig.size()) return 0;
    vector<array<lint, 2>> dp(k);
    dp[0][0]=1;

    for (lint x: dig) {
        vector<array<lint, 2>> nq(k);
        for (int i=0; i<k; i++) {
            if (dp[i][0]) {
                nq[i][0]+=dp[i][0]*(x+1);
                if (i+1<k) nq[i+1][1]+=dp[i][0]*(p-x-1);
            }
            if (dp[i][1]) {
                nq[i][0]+=dp[i][1]*x;
                if (i+1<k) nq[i+1][1]+=dp[i][1]*(p-x);
            }
        }
        dp.swap(nq);
    }

    lint less=0;
    for (int i=0; i<k; i++) less+=dp[i][0];
    return all-less;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        lint n, p, k;
        cin >> n >> p >> k;
        cout << run(n, p, k) << '\n';
    }
}