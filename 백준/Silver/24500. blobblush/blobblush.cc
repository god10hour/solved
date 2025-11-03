#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int64_t n, m=1;
    cin >> n;
    while (m<n) m=m*2+1;
    if (m==n)
        cout << 1 << '\n' << n;
    else
        cout << 2 << '\n' << (m^n) << '\n' << n;
}