#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int a, b, d, n, r=1, s=0, mod=1000;
    cin >> a >> b >> d >> n;
    vector<int> v(n+1);
    v[0]=1;
    for (int i=1; i<=n; i++) {
        if (i>=a) (s+=v[i-a])%=mod;
        if (i>=b) (s-=v[i-b]-mod)%=mod;
        if (i>=d) (r-=v[i-d]-mod)%=mod;
        r+=v[i]=s;
    }
    cout << r%mod << '\n';
}