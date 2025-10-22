#include <bits/stdc++.h>
using namespace std;
#define ll long long
int p[12]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

ll GCD(ll a,ll b) {
    return b?GCD(b, a%b):a;
}

ll Pow(__int128 a, __int128 n, __int128 p) {
    __int128 r=1;
    a%=p;
    while(n) {
        if (n%2)
            r=r*a%p;
        a=a*a%p;
        n/=2;
    }
    return r;
}

bool f(ll n, ll a) {
    ll k=n-1;
    while(1) {
        ll d=Pow(a, k, n);
        if (k%2)
            return d==1 || d==n-1;
        if (d==n-1)
            return 1;
        k/=2;
    }
}

bool isPrime(ll n) {
    if (n<2)
        return 0;
    for (int i=0; i<12; i++) {
        if (n==p[i])
            return 1;
        if (n%p[i]==0)
            return 0;
        if (!f(n, p[i]))
            return 0;
    }
    return 1;
}

ll div(__int128 n) {
    if (n%2==0)
        return 2;
    if (isPrime(n))
        return n;

    __int128 x=rand()%(n-2)+2, y=x, c=rand()%10+1, g=1;

    while (g==1) {
        x=(x*x%n+c)%n;
        y=(y*y%n+c)%n;
        y=(y*y%n+c)%n;
        g=GCD(abs(x-y),n);
        if (g==n)
            return div(n);
    }
    if (isPrime(g))
        return g;
    return div(g);
}

int main() {
    ll n;
    cin >> n;
    vector<ll> s;

    while (n>1) {
        ll d=div(n);
        s.push_back(d);
        n/=d;
    }
    sort(s.begin(), s.end());
    for (ll i=0; i<s.size(); i++)
        cout << s[i] << '\n';
}