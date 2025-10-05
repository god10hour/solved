#include <bits/stdc++.h>
using namespace std;

bool prime(int n) {
    if (n<2) return 0;
    for (int i=2; i*i<=n; i++)
        if (n%i==0)
            return 0;
    return 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int m, n, k=-1, s=0;
    cin >> m >> n;
    for (int i=n; i>=m; i--)
        if (prime(i))
            s+=i, k=i;
    if (s)
        cout << s << '\n';
    cout << k;
}