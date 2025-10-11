#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> v(1<<n);
    for (int i=0; i<(1<<n); i++)
        cin >> v[i];
    for (int i=0; i<(1<<n); i++)
        for (int x=0; x<n; x++)
            for (int y=x+1; y<n; y++) {
                int k=i^(1<<x)^(1<<y);
                if (v[i]+v[k]<v[i&k]+v[i|k])
                    return !(cout << i << ' ' << k);
            }
    cout << -1;
}