#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, r=0;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (int i=0; i<n; i++)
        cin >> v[i].first >> v[i].second;
    ranges::sort(
        v, [](auto &a, auto &b) {
            if (!a.first) return false;
            if (!b.first) return true;
            if (a.second || b.second)
                return a.second*b.first<b.second*a.first;
            return a.first<b.first;
        }
    );
    for (int i=0; i<n; i++) r=(r+r*v[i].first+v[i].second)%40000;
    cout << r << '\n';
}