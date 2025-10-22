#include <bits/stdc++.h>
#define int uint64_t
using namespace std;

int pow(__int128 n, __int128 k, const int &mod) {
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

    __int128 x=rand()%(n-2)+2, y=x, c=rand()%10+1, g=1;
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

vector<int> factor(int n) {
    vector<int> r;
    while (n>1) {
        int d=div(n);
        r.push_back(d);
        n/=d;
    }
    sort(r.begin(), r.end());
    return r;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    while (1) {
        int n, r=2;
        cin >> n;
        if (!n) return 0;
        while (n%2==0) n/=2;

        auto v=factor(n), p=v;
        p.erase(unique(p.begin(), p.end()), p.end());
        for (auto &i: p) {
            int k=upper_bound(v.begin(), v.end(), i)-
                  lower_bound(v.begin(), v.end(), i);
            r*=k*2+1;
        }
        cout << r << '\n';
    }
}