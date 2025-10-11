#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int floorsum(int n, int m, int a, int b) {
    int r=0;
    while (1) {
        if (a>=m) r+=(n-1)*n*(a/m)/2, a%=m;
        if (b>=m) r+=n*(b/m), b%=m;
        int x=n*a+b;
        if (x<m) break;
        n=x/m, b=x%m;
        swap(m, a);
    }
    return r;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int p, q, n;
        cin >> p >> q >> n;
        cout << p*(n*(n+1)/2)-q*floorsum(n+1, q, p, 0) << '\n';
    }
}