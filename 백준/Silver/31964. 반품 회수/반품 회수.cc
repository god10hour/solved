#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, r;
    cin >> n;
    vector<int> v(n), w(n);
    for (int i=0; i<n; i++) cin >> v[i];
    for (int i=0; i<n; i++) cin >> w[i];
    r=max(v[n-1], w[n-1]);
    for (int i=n-1; i>0; i--)
        r=max(r+v[i]-v[i-1], w[i-1]);
    cout << r+v[0];
}