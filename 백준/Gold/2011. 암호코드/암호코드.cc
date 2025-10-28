#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const int mod=1e6;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    int n=s.length();
    vector<int> a(n+1, 0), dp(n+1, 0);
    for (int i=0; i<n; i++) a[i+1]=s[i]-'0';
    if (a[1]==0) return !(cout << 0);

    dp[1]=dp[0]=1;
    for (int i=2; i<=n; i++) {
        if (a[i]>0) dp[i]+=dp[i-1];
        if (a[i-1]>0 && a[i-1]*10+a[i]<=26) dp[i]+=dp[i-2];
        dp[i]%=mod;
        if (dp[i]==0) break;
    }
    cout << dp[n];
}
