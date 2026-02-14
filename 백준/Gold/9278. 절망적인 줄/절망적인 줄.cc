#include <bits/stdc++.h>
using namespace std;
constexpr int mod=1e6;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    string s;
    while (cin >> s) {
        int n=s.length(), k=n/2;
        int l=0, r=0;
        for (char c: s)
            if (c=='(')
                l++;
            else if (c==')') r++;

        vector<int> dp(k+1, 0), ndp(k+1, 0);
        dp[0]=1;
        for (int i=0; i<n; i++) {
            ranges::fill(ndp, 0);
            char c=s[i];
            for (int j=0; j<=k; j++) {
                if (!dp[j]) continue;
                if (j*2-i<0) continue;
                if (c=='(' || c=='.')
                    if (j+1<=k) {
                        int x=ndp[j+1]+dp[j];
                        if (x>=mod) x-=mod;
                        ndp[j+1]=x;
                    }
                if (c==')' || c=='.')
                    if (2*j>=i+1) {
                        int x=ndp[j]+dp[j];
                        if (x>=mod) x-=mod;
                        ndp[j]=x;
                    }
            }
            dp.swap(ndp);
        }
        cout << dp[k]%mod << '\n';
    }
}