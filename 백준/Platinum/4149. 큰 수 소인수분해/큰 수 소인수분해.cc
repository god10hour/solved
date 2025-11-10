#include <bits/stdc++.h>
using namespace std;
using lint=uint64_t;

lint pow(__int128 n, __int128 k, lint mod) {
    __int128 r=1;
    while (k) {
        if (k&1)
            r=r*n%mod;
        n=n*n%mod;
        k/=2;
    }
    return r;
}

constexpr int base[]={
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
};
bool prime(lint n) {
    if (n<2) return 0;
    auto f=[](lint n, lint a)->bool {
        lint k=n-1;
        while (true) {
            lint d=pow(a, k, n);
            if (k&1) return d==1 || d==n-1;
            if (d==n-1) return 1;
            k/=2;
        }
    };

    for (const auto &p: base) {
        if (n==p) return 1;
        if (n%p==0) return 0;
        if (!f(n, p)) return 0;
    }
    return 1;
}

lint div(__int128 n) {
    if (n%2==0) return 2;
    if (prime(n)) return n;

    __int128 x=rand()%(n-2)+2, y=x;
    __int128 c=rand()%10+1, g=1;
    while (g==1) {
        x=(x*x+c)%n;
        y=(y*y+c)%n;
        y=(y*y+c)%n;
        g=gcd(abs(x-y), n);
        if (g==n) return div(n);
    }

    if (prime(g)) return g;
    return div(g);
}

vector<lint> factor(lint n) {
    vector<lint> r;
    while (n>1) {
        lint d=div(n);
        r.push_back(d);
        n/=d;
    }
    sort(r.begin(), r.end());
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    lint n;
    cin >> n;
    auto a=factor(n);
    for (auto x: a)
        cout << x << '\n';
}