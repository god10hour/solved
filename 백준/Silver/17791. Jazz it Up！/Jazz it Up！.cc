#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i=1; i++; )
        if (gcd(n, i)==1)
            return !(cout << i);
}