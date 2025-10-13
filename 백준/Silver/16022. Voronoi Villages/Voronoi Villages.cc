#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(1);
    int n;
    cin >> n;
    vector<int> v(n), dis(n-2);
    for (int i=0; i<n; i++)
        cin >> v[i], v[i]*=2;
    sort(v.begin(), v.end());
    for (int i=1; i<n-1; i++)
        dis[i-1]=(v[i]-v[i-1])/2+(v[i+1]-v[i])/2;
    sort(dis.begin(), dis.end());
    cout << dis[0]/2.0;
}
