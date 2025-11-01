#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k, s=0;
    cin >> n >> k;
    vector<int> v(n);
    for (int i=0; i<n; i++) cin >> v[i];
    sort(v.begin(), v.end(), greater<int>());
    for (int i=0; i<n; i++) {
        s+=v[i];
        if (s>=k)
            return !(cout << i+1);
    }
}