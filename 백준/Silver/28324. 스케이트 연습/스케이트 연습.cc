#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int64_t n, s=0, c=0;
    cin >> n;
    vector<int64_t> v(n);
    for (int i=0; i<n; i++) cin >> v[i];
    for (int i=n-1; i>=0; i--)
        c=min(c+1, v[i]), s+=c;
    cout << s;
}