#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k, s=0, r=0;
    unordered_map<int, int> c;
    c[0]=1;
    cin >> n >> k;
    for (int i=0; i<n; i++) {
        int x;
        cin >> x;
        s+=x;
        if (c.count(s-k))
            r+=c[s-k];
        c[s]++;
    }
    cout << r;
}