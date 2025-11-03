#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> v(n+2, 0);
    for (int i=1; i<=n; i++) cin >> v[i];
    for (int i=2; i<n; i++) {
        if (v[i]==v[i-1] || v[i]==v[i+1])
            return !(cout << "NO");
        if (v[i]<v[i-1] && v[i]<v[i+1])
            return !(cout << "NO");
    }
    cout << "YES";
}