#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(1);
    int t=0;
    while (++t) {
        int n;
        cin >> n;
        if (!n) return 0;
        vector<int> v(n);
        for (int i=0; i<n; i++) cin >> v[i];
        cout << "Case " << t << ": ";
        cout << (v[n/2]+v[(n-1)/2])/2.0 << '\n';
    }
}