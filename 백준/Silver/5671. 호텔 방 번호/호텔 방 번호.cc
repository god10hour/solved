#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    array<int, 5001> pref={};
    for (int i=1; i<5001; i++) {
        vector c(10, false);
        bool z=true;
        int n=i;
        while (n) {
            if (c[n%10]) {
                z=false;
                break;
            }
            c[n%10]=true, n/=10;
        }
        pref[i]=pref[i-1]+z;
    }
    int l, r;
    while (cin >> l >> r)
        cout << pref[r]-pref[l-1] << '\n';
}