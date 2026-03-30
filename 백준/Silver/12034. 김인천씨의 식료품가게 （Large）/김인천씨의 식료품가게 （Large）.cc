#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int T;
    cin >> T;
    for (int t=0; t<T; t++) {
        int n;
        cin >> n;
        vector<int> p(n*2), r(n);
        for (int &x: p) cin >> x;
        for (int i=0; i<n; i++) {
            r[i]=p.front();
            p.erase(p.begin());
            p.erase(ranges::lower_bound(p, r[i]/3*4));
        }
        cout << "Case #" << t+1 << ": ";
        for (int i=0; i<n; i++) cout << r[i] << ' ';
        cout << '\n';
    }
}