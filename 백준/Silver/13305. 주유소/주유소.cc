#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, c=1e9;
    int64_t r=0;
    cin >> n;
    n--;
    vector<int> dis(n), cos(n);
    for (int i=0; i<n; i++) cin >> dis[i];
    for (int i=0; i<n; i++) cin >> cos[i];
    for (int i=0; i<n; i++) {
        c=min(c, cos[i]);
        r+=c*dis[i];
    }
    cout << r;
}
