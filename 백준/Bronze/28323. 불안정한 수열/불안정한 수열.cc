#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i=0; i<n; i++) cin >> v[i];
    int c=1, s=v[0]%2;
    for (int i=1; i<n; i++) {
        int k=v[i]%2;
        if (k!=s) c++, s=k;
    }
    cout << c;
}