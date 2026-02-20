#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    array<int, 101> dp={0, 1};
    for (int i=2; i<101; i++) {
        dp[i]=dp[i-1]+1;
        if (i>=10) dp[i]=min(dp[i], dp[i-10]+1);
        if (i>=25) dp[i]=min(dp[i], dp[i-25]+1);
    }

    int t;
    cin >> t;
    while (t--) {
        int64_t n, r=0;
        cin >> n;
        while (n) r+=dp[n%100], n/=100;
        cout << r << '\n';
    }
}