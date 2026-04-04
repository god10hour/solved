#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        lint g, h, p=1;
        cin >> g >> h;
        while (p<=g) p*=h;

        lint b=(p+g-1)/g*g, a=h*b+g;
        cout << a << ' ' << b << '\n';
    }
}