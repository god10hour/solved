#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

lint pow_mod(lint n, int k, lint mod) {
    lint r=1;
    while (k) {
        if (k&1) r=r*n%mod;
        n=n*n%mod;
        k/=2;
    }
    return r;
}

vector<pair<lint, int>> fac(lint n) {
    vector<pair<lint, int>> r;
    int c=0;
    while (n%2==0) n/=2, c++;
    r.emplace_back(2, c);
    for (lint p=3; p*p<=n; p+=2) {
        if (n%p) continue;
        int e=0;
        while (n%p==0) n/=p, e++;
        r.emplace_back(p, e);
    }
    if (n>1) r.emplace_back(n, 1);
    return r;
}

lint phi(lint n) {
    lint r=n;
    auto div=fac(n);
    for (auto &p: div|views::keys) r=r/p*(p-1);
    return r;
}

lint ord(lint a, lint mod) {
    if (mod==1) return 1;
    lint r=phi(mod);
    auto div=fac(r);
    for (auto &p: div|views::keys) {
        while (r%p==0 && pow_mod(a, r/p, mod)==1) r/=p;
    }
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    lint n;
    cin >> n;
    auto div=fac(n);
    for (auto &e: div|views::values)
        if (e>1) return !(cout << -1 << '\n');
    lint r=1;
    for (auto &p: div|views::keys) {
        lint m=p-1;
        if (gcd(n, m)!=1) return !(cout << -1 << '\n');
        lint u=ord(n%m, m);
        r=r/gcd(r, u)*u;
    }

    cout << r << '\n';
}