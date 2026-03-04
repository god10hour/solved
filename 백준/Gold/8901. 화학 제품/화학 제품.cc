#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        int a, b, c, ab, bc, ca;
        cin >> a >> b >> c;
        cin >> ab >> bc >> ca;

        int r=0;
        for (int k=0; k<=min(a, b); k++) {
            int u=min(b-k, c);
            int v=min(c-u, a-k);
            r=max(r, k*ab+u*bc+v*ca);
            v=min(c, a-k);
            u=min(b-k, c-v);
            r=max(r, k*ab+u*bc+v*ca);
        }
        cout << r << '\n';
    }
}