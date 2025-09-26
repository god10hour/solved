#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const int MOD=1000000007;

int Pow(int n, int k) {
    int r=1;
    while (k) {
        if (k&1)
            r=(r*n)%MOD;
        n=(n*n)%MOD;
        k/=2;
    }
    return r;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int R, G, B, k;
        cin >> R >> G >> B >> k;
        int r, a, b;
        a=Pow(B, k)*Pow(1+B, MOD-k-1)%MOD;
        a=R*(1-a+MOD)%MOD;
        b=k*(G*Pow(B, MOD-2)%MOD)%MOD;
        r=(k+a+b)%MOD;
        cout << r << '\n';
    }
}