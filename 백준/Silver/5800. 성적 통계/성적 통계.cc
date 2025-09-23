#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    for (int i=1; i<=t; i++) {
        int n, m=0;
        cin >> n;
        vector<int> v(n);
        for (int j=0; j<n; j++)
            cin >> v[j];
        sort(v.begin(), v.end());
        for (int j=0; j<n-1; j++)
            m=max(m, v[j+1]-v[j]);
        cout << "Class " << i << '\n';
        cout << "Max " << v.back() << ", Min " << v.front();
        cout << ", Largest gap " << m << '\n';
    }
}