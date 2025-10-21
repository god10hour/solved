#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i=0; i<m; i++)
            cout << string(n, 'X') << '\n';
        cout << '\n';
    }
}