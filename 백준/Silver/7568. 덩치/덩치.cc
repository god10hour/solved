#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (int i=0; i<n; i++) cin >> v[i].first >> v[i].second;
    for (auto p: v) {
        int r=1;
        for (auto pr2: v)
            if (pr2.first>p.first && pr2.second>p.second)
                r++;
        cout << r << ' ';
    }
}