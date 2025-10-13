#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    double s=0;
    cin >> n;
    vector<int> v(n);
    for (int i=0; i<n; i++)
        cin >> v[i], s+=v[i];
    sort(v.begin(), v.end());
    cout << fixed << setprecision(6) << s/n << '\n';
    if (n%2)
        cout << v[(n-1)/2];
    else cout << (v[(n-1)/2]+v[(n-1)/2+1])/2.0;
}
