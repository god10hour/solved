#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i=2; i<1000001; i++) {
        if (n<m) swap(n, m);
        if (n==m) return !(cout << n);
        if (n%i==0) n/=i;
        else if (m%i==0) m/=i;
        else i++;
        i--;
    }
    cout << 1;
}