#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int> v(n*2);
    iota(v.begin(), v.end(), 1);
    while (q--) {
        int k;
        cin >> k;
        if (k) rotate(v.begin(), v.begin()+k, v.end());
        else {
            vector<int> u(n*2);
            for (int i=0; i<n; i++)
                u[i*2]=v[i], u[i*2+1]=v[i+n];
            v.swap(u);
        }
    }
    for (int i=0; i<n*2; i++)
        cout << v[i] << '\n';
}
