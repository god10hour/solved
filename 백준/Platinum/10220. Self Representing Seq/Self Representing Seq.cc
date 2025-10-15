#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, t;
    cin >> t;
    while (t--) {
        cin >> n;
        if (n<=3 || n==6) cout << "0\n";
        else if (n==4) cout << "2\n";
        else cout << "1\n";
    }
}