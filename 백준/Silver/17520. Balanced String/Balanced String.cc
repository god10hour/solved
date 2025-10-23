#include <bits/stdc++.h>
using namespace std;

int pow(int64_t n, int k, int mod) {
    int64_t r=1;
    while (k) {
        if (k&1)
            r=r*n%mod;
        n=n*n%mod;
        k/=2;
    }
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    cout << pow(2, (n+1)/2, 16769023);
}