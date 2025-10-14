#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int64_t n, c=0;
    cin >> n;
    vector<int> v(n), s(n, 0);
    for (int i=0; i<n; i++) cin >> v[i];
    for (int i=1; i<n; i++)
        s[i]=max<int>(ceil(log2((double)v[i-1]/v[i]))+s[i-1], 0), c+=s[i];
    cout << c;
}