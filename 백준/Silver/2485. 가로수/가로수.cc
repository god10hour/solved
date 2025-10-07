#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, d, c=0;
    cin >> n;
    vector<int> v(n);
    for (int i=0; i<n; i++) cin >> v[i];
    for (int i=0; i<n-1; i++) v[i]=v[i+1]-v[i];
    d=v[0];
    for (int i=1; i<n-1; i++) d=gcd(d, v[i]);
    for (int i=0; i<n-1; i++) c+=v[i]/d-1;
    cout << c;
}