#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, c=0;
    cin >> n;
    vector<int> v(n);
    for (int &x: v) cin >> x;
    ranges::sort(v);

    for (int i=0; i<n; i++) {
        int l=0, r=n-1;
        while (l<r) {
            if (l==i) { l++; continue; }
            if (r==i) { r--; continue; }

            int x=v[l]+v[r];
            if (x==v[i]) { c++; break; }
            if (x<v[i]) l++;
            if (x>v[i]) r--;
        }
    }
    cout << c << '\n';
}