#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    map<int, int> mem;
    int n, m, k;
    cin >> n >> m;
    for (int i=0; i<m; i++)
        cin >> k, mem[k]=i;
    vector<pair<int, int>> v(mem.begin(), mem.end());
    sort(v.begin(), v.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.second<b.second;
    });
    for (int i=0; i<min<int>(n, v.size()); i++)
        cout << setfill('0') << setw(8) << v[i].first << '\n';
}