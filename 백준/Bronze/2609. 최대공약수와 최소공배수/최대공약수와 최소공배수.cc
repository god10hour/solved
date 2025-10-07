#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int d=gcd(n, m);
    cout << d << ' ' << n*m/d;
}