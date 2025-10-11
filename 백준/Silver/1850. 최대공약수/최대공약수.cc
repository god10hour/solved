#include <bits/stdc++.h>
using namespace std;

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int64_t n, m, d;
    cin >> n >> m;
    d=gcd(n, m);
    cout << string(d, '1');
}