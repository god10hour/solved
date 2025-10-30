#include <bits/stdc++.h>
#define int uint64_t
using namespace std;

int pow(__int128 n, __int128 k, int mod) {
    __int128 r=1;
    while (k) {
        if (k&1)
            r=r*n%mod;
        n=n*n%mod;
        k/=2;
    }
    return r;
}

const int base[12]={
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
};
bool prime(int n) {
    if (n<2) return 0;
    auto f=[](int n, int a)->bool {
        int k=n-1;
        while (true) {
            int d=pow(a, k, n);
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

int div(__int128 n) {
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

set<int> factor(int n) {
    set<int> r;
    r.insert(1);
    while (n>1) {
        int d=div(n);
        n/=d;
        vector<int> v;
        for (int x: r) v.push_back(d*x);
        r.insert(v.begin(), v.end());
    }
    return r;
}

int four(int n) {
    if (n==0) return 1;
    auto fct=factor(n);
    int r=0;
    for (int x: fct) {
        if (x>sqrt(n)) break;
        if (x%4) r+=x;
        if (x*x==n) continue;
        if (n/x%4) r+=n/x;
    }
    return r*8;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    auto fct=factor(n);
    int a=four(n), b=a;
    for (int i=1; i*i<=n; i++)
        b+=four(n-i*i)*2;
    cout << a << ' ' << b;
}