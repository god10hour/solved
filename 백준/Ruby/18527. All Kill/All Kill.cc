#include <bits/stdc++.h>
using namespace std;
constexpr int mod=998244353;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, t, s=0;
    cin >> n >> t;
    vector<int> v(n);
    for (int &x: v) cin >> x, s+=x;
    int r=1, w=t+1;
    for (int i=n-2; i>=0; i--) {
        w-=v[i+1]-1;
        r=1LL*r*w%mod;
    }
    r=1LL*r*(t-s+1)%mod;
    cout << r << '\n';
}