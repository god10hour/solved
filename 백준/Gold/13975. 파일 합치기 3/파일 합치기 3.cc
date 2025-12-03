#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        lint n, r=0;
        priority_queue<lint, vector<lint>, greater<>> pq;
        cin >> n;
        for (int i=0; i<n; i++) {
            int x;
            cin >> x;
            pq.push(x);
        }

        while (pq.size()>1) {
            lint a=pq.top(); pq.pop();
            lint b=pq.top(); pq.pop();
            pq.push(a+b);
            r+=a+b;
        }
        cout << r << '\n';
    }
}