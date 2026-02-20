#include <bits/stdc++.h>
using namespace std;
constexpr int N=1e6;
constexpr int mod=1e9+7;
array<int64_t, N> a, b;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    a[0]=7, b[0]=3;
    for (int i=1; i<N; i++) {
        a[i]=(a[i-1]*3+b[i-1]*4)%mod;
        b[i]=(a[i-1]+b[i-1]*2)%mod;
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << a[n-1] << '\n';
    }
}