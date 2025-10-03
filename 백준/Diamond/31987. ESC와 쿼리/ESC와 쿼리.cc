#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const int MOD=1e9+7;

int norm(int x) {
    x%=MOD;
    if (x<0) x+=MOD;
    return x;
}
static int POW(int n, int k) {
    int r=1;
    n=norm(n);
    while (k) {
        if (k&1) r=r*n%MOD;
        n=n*n%MOD;
        k/=2;
    }
    return r;
}

struct cpx {
    int a, b;
    cpx(int _a=0, int _b=0): a(norm(_a)), b(norm(_b)) {}

    cpx inv() const {
        int i=POW(norm(norm(a*a) + norm(b*b)), MOD-2);
        return cpx(norm(a*i), norm(-b*i));
    }
    cpx operator+(const cpx &o) const {
        return cpx(a+o.a, b+o.b);
    }
    cpx operator-(const cpx &o) const {
        return cpx(a-o.a, b-o.b);
    }
    cpx operator*(const cpx &o) const {
        return cpx(norm(a*o.a-b*o.b), norm(a*o.b+b*o.a));
    }
    cpx operator/(const cpx &o) const {
        return *this*o.inv();
    }

    cpx pow(int k) const {
        cpx base=*this, r(1, 0);
        while (k) {
            if (k&1) r=r*base;
            base=base*base;
            k/=2;
        }
        return r;
    }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int q;
    cin >> q;
    cpx base(1, 2);

    auto ESC=[&](const cpx &w, int i, int j) {
        if (w.a==1 && w.b==0)
            return cpx((j-i+1)%MOD, 0);
        cpx n=cpx(1, 0)-w.pow(j-i+1);
        cpx d=cpx(1, 0)-w;
        return w.pow(i)*(n/d);
    };
    while (q--) {
        int i, j, k;
        cin >> i >> j >> k;
        cpx S=ESC(base.pow(k), i, j);
        cout << norm(S.a) << '\n';
    }
}