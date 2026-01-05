#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (int i=0; i<n; i++) {
        v[i].first=i+1;
        cin >> v[i].second;
    }
    while (!v.empty()) {
        auto [idx, nxt]=v.front();
        v.erase(v.begin());
        cout << idx << ' ';
        if (nxt>0) for (int i=0; i<nxt-1; i++)
            v.push_back(v.front()),
            v.erase(v.begin());
        else for (int i=0; i<-nxt; i++)
            v.insert(v.begin(), v.back()),
            v.erase(v.end()-1);
    }
}