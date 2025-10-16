#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t, l, r;
    cin >> t;
    while (t--) {
        cin >> l >> r;
        if (r>3) cout << r << '\n';
        else {
            int n=0, c=0;
            for (int i=r; i>=l; i--)
                n+=(1<<i)*pow(10, r-i);
            while (n%2==0)
                n/=2, c++;
            cout << c << '\n';
        }
    }
}
