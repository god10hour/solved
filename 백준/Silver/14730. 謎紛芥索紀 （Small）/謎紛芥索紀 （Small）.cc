#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, a, b, r=0;
    cin >> n;
    for (int i=0; i<n; i++)
        cin >> a >> b, r+=a*b;
    cout << r;
}