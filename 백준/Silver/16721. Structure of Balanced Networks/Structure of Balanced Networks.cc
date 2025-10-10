#include <bits/stdc++.h>
using namespace std;
static bitset<25000000> B;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    char c;
    cin >> n;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++) {
            cin >> c;
            if (c=='+')
                B.set(i*n+j);
        }
    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << (B.test(u*n+v)? '+': '-') << '\n';
    }
}
