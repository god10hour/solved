#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<int64_t> v;
    for (int i=2001; v.size()<30; i+=2) {
        bool z=1;
        for (int j=2; j*j<=i; j++)
            if (i%j==0) {
                z=0; break;
            }
        if (z) v.push_back(i);
    }
    int n, k;
    cin >> k >> n;
    for (int i=0; i<k; i++, cout << '\n')
        for (int j=1; j<=n; j++)
            cout << v[i]*j << ' ';
}