#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    while (cin >> n >> m, n) {
        if (n%m==0) cout << "multiple\n";
        else if (m%n==0) cout << "factor\n";
        else cout << "neither\n";
    }
}