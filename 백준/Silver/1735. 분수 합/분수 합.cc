#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int y=lcm(b, d);
    int x=a*(y/b)+c*(y/d);
    cout << x/gcd(x, y) << ' ' << y/gcd(x, y);
}