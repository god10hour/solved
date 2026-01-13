#include <bits/stdc++.h>
using namespace std;
using lint=uint64_t;
using lodb=long double;

static constexpr lint LOOP =5e6;
static constexpr lodb GAMMA=0.577215664901532860606512090082402431L;
static constexpr array coef {
    2.0L, 12.0L, 120.0L, 252.0L,
    240.0L, 132.0L, 32760.0L/691.0L, 12.0L
};


lodb harmonic_small(lint n) {
    lodb s=0.0L, c=0.0L;
    for (lint i=1; i<=n; i++) {
        lodb y=1.0L/(i-c), t=s+y;
        c=t-s-y, s=t;
    }
    return s;
}
lodb harmonic_asym(lint n) {
    lodb x=lodb(n);
    array<lodb, 8> inv{};
    inv[0]=1.0L/x, inv[1]=inv[0]*inv[0];
    for (int i=2; i<8; i++)
        inv[i]=inv[1]*inv[i-1];

    lodb r=logl(x)+GAMMA;
    int d=1;
    for (int i=0; i<8; i++)
        r+=d*inv[i]/coef[i], d*=-1;
    return r;
}
lodb harmonic(lint n) {
    if (n==0) return 0.0L;
    if (n<=3'000'000)
        return harmonic_small(n);
    return harmonic_asym(n);
}

lodb tail_sum(lint n, lint k) {
    if (k==0) return 0.0L;
    if (k==n) return harmonic(n);
    lint m=n-k;

    if (k<=LOOP) {
        lodb s=0.0L, c=0.0L;
        for (lint i=0; i<k; i++) {
            lodb term=1.0L/(n-i);
            lodb y=term-c, t=s+y;
            c=t-s-y, s=t;
        }
        return s;
    }
    if (m<=3'000'000)
        return harmonic(n)-harmonic_small(m);
    
    array<lodb, 8> invn{}, invm{};
    invn[0]=1.0L/n, invn[1]=invn[0]*invn[0];
    for (int i=2; i<8; i++)
        invn[i]=invn[1]*invn[i-1];
    invm[0]=1.0L/m, invm[1]=invm[0]*invm[0];
    for (int i=2; i<8; i++)
        invm[i]=invm[1]*invm[i-1];

    lodb r=log1pl(lodb(k)/m);
    int d=1;
    for (int i=0; i<8; i++)
        r+=d*(invn[i]-invm[i])/coef[i], d*=-1;
    return r;
}

int main() {
    basic_ostream<char>::sync_with_stdio(false);
    lint n, k;
    cin >> n >> k;
    cout << fixed << setprecision(15) << n*tail_sum(n, k) << '\n';
}
