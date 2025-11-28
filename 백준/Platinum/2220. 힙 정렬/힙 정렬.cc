#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> v(n+1);
    iota(v.begin(), v.end(), 0);
    for (int i=2; i<=n; i++) {
        int j=i-1;
        swap(v[i], v[j]);
        while (j>1)
            swap(v[j], v[j/2]), j/=2;
    }
    for (int i=1; i<=n; i++) cout << v[i] << ' ';
}