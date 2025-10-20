#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int d, n, m, k;
    cin >> d >> n >> m >> k;
    auto f=[&](int x) {
        return x%d? d-x%d: 0;
    };
    if (f(n)>f(m)) swap(n, m);
    
    int mandu=(n+m+k)/d;
    if (k/d+n/d+m/d==mandu) cout << k;
    else if ((k-f(n))/d+(n+f(n))/d+m/d==mandu) cout << k-f(n);
    else if ((k-f(m))/d+n/d+(m+f(m))/d==mandu) cout << k-f(m);
    else cout << k-f(n)-f(m);
}