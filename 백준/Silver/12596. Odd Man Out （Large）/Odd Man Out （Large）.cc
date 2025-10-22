#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    for (int t=0; t<T; t++) {
        int n, k, r=0;
        cin >> n;
        for (int i=0; i<n; i++)
            cin >> k, r^=k;
        cout << "Case #" << t+1 << ": " << r << '\n';
    }
}