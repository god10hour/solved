#include <bits/stdc++.h>
#define int int64_t
using namespace std;

bool f(int x) {
    int r=sqrtl(x);
    return r*r==x;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> v(n), u(n);
    for (int i=0; i<n; i++)
        cin >> v[i], u[i]=v[i];
    sort(u.begin(), u.end());
    for (int i=0; i<n; i++) {
        int d=gcd(v[i], u[i]);
        v[i]/=d, u[i]/=d;
        if (f(v[i]) && f(u[i])) continue;
        return !(cout << "NO");
    }
    cout << "YES";
}