#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const int MOD=10007;

int f[1001]={1, 1};

int Pow(int a, int x) {
    int r=1;
    while (x) {
        if (x&1)
            r=r*a%MOD;
        a=a*a%MOD;
        x/=2;
    }
    return r;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int i=2; i<1001; i++)
        f[i]=i*f[i-1]%MOD;
    int n, k;
    cin >> n >> k;
    cout << f[n]*Pow(f[n-k]*f[k]%MOD, MOD-2)%MOD << '\n';
}