#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr lint base=1e9;

bool prime(lint n) {
    if (n<2) return false;
    if (n%2==0) return n==2;
    for (lint p=3; p*p<=n; p+=2) if (n%p==0) return false;
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    lint n, m;
    cin >> n >> m;
    if (m==1) return !(cout << "0 1" << '\n');
    if (n>1 && m==2) {
        lint k=n*2-1;
        if (k-2>base && prime(k) && prime(k-2))
            return !(cout << n-2 << ' ' << 2 << '\n');
    }
    lint k=n*2-1<base? n: max(base-n, n/3);
    cout << n << ' ' << min(m, k+1) << '\n';
}