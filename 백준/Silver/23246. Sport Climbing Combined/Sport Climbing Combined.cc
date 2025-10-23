#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<tuple<int, int, int>> v(n);
    for (int i=0; i<n; i++) {
        int x, a, b, c;
        cin >> x >> a >> b >> c;
        v[i]={a*b*c, a+b+c, x};
    }
    sort(v.begin(), v.end());
    for (int i=0; i<3; i++) cout << get<2>(v[i]) << ' ';
}