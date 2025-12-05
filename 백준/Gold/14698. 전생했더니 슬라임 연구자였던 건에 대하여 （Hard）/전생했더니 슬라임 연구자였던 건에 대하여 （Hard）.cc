#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr int mod=1e9+7;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        lint n, r=1;
        priority_queue<lint, vector<lint>, greater<>> pq;
        cin >> n;
        for (int i=0; i<n; i++) {
            lint x;
            cin >> x;
            pq.push(x);
        }

        while (pq.size()>1) {
            lint a=pq.top(); pq.pop();
            lint b=pq.top(); pq.pop();
            pq.push(a*b);
            r=r*(a*b%mod)%mod;
        }
        cout << r << '\n';
    }
}