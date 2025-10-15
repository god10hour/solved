#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> v(n), dp(n, 0);
    for (int i=0; i<n; i++) cin >> v[i];
    for (int i=0; i<n; i++) {
        int rem=v[i];
        dp[i]=max(dp[i], dp[i-1]);
        for (int j=i+1; j<n; j++) {
            rem=v[j]-rem;
            if (rem<0) break;
            if (rem==0) dp[j]=dp[i-1]+1;
        }
    }
    cout << n-dp[n-1];
}