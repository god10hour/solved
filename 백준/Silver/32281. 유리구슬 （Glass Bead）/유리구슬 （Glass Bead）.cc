#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, r=0, c=0;
    string s;
    cin >> n >> s;
    vector<int> v(n+1, 0);
    for (int i=0; i<n; i++) v[i+1]=i+v[i]+1;
    for (int i=0; i<n; i++)
        if (s[i]=='0')
            r+=v[c], c=0;
        else c++;
    r+=v[c];
    cout << r;
}