#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> v(n), u(n);
    for (int i=0; i<n; i++) {
        int x, y;
        cin >> x >> y;
        v[i]=x+y, u[i]=x-y;
    }
    ranges::sort(v);
    ranges::sort(u);
    cout << max(v[n-1]-v[0], u[n-1]-u[0]) << '\n';
}