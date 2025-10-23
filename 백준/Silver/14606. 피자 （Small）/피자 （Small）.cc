#include <bits/stdc++.h>
using namespace std;

int f(int n) {
    if (n==1) return 0;
    int a=n/2, b=n-a;
    return a*b+f(a)+f(b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    cout << f(n);
}