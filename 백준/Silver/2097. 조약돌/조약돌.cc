#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    if (n<3) return !(cout << 4);
    for (int i=2; i<n; i++) {
        if (n<=i*i) return !(cout << (i-1)*4);
        if (n<=i*(i+1)) return !(cout << (i-1)*4+2);
    }
}