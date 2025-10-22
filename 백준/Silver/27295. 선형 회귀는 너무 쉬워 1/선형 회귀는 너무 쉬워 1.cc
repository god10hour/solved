#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, b, X=0, Y=0, z=-1;
    cin >> n >> b;
    for (int i=0; i<n; i++) {
        int x, y;
        cin >> x >> y;
        X+=x, Y-=y;
    } Y+=n*b;
    if (X<0) z*=-1, X*=-1;
    if (Y<0) z*=-1, Y*=-1;

    if (X==0) return !(cout << "EZPZ");
    if (Y%X==0) return !(cout << z*Y/X);
    int d=gcd(X, Y);
    cout << z*Y/d << '/' << X/d;
}