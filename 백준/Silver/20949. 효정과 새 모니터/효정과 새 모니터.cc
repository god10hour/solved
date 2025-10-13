#include <bits/stdc++.h>
using namespace std;


int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (int i=0; i<n; i++) {
        int h, w;
        cin >> h >> w;
        v[i]={h*h+w*w, i+1};
    }
    sort(v.begin(), v.end(), [](auto a, auto b) {
        if (a.first==b.first)
            return a.second<b.second;
        return a.first>b.first;
    });
    for (int i=0; i<n; i++) cout << v[i].second << '\n';
}
