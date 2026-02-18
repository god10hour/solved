#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<pair<lint, lint>> v(n), mask(m);
    for (auto &[l, r]: v) cin >> l >> r;
    for (auto &[p, x]: mask) cin >> p >> x;
    ranges::sort(v);
    ranges::sort(mask);

    int r=0;
    priority_queue<lint, vector<lint>, greater<>> pq;
    for (int i=0, j=0; i<m; i++) {
        auto &[p, x]=mask[i];
        while (j<n && p>=v[j].first) pq.push(v[j++].second);
        while (!pq.empty() && p>pq.top()) pq.pop();
        while (!pq.empty() && x) r++, x--, pq.pop();
    }
    cout << r << '\n';
}