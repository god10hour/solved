#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const int MOD=1e9+7;

int phi(int x) {
    int r=x;
    if (x%2==0) {
        while (x%2==0)
            x/=2;
        r-=r/2;
    }
    for (int i=3; i*i<=x; i+=2)
        if (x%i==0) {
            while (x%i==0)
                x/=i;
            r-=r/i;
        }
    if (x>1) r-=r/x;
    return r;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, k, r=1;
        cin >> n;
        for (int i=0; i<n; i++) {
            cin >> k;
            r=r*phi(k)%MOD;
        }
        cout << r << '\n';
    }
}