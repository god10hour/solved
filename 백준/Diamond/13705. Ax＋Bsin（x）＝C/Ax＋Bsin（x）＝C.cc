#include <bits/stdc++.h>
using namespace std;
using Int=__int128;
using Float=__float128;
constexpr Float TAU=2.0L*3.1415926535897932384626433832795Q;

Float sine(Float x) {
    x-=Int(x/TAU)*TAU;
    Float r=x, y=x;
    const Float s=-x*x;
    for (Float d=2; d<30; d+=2)
        y*=s/(d*(d+1)), r+=y;
    return r;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(6);
    Float a, b, c, l, r, x;
    long double A, B, C;
    const Float U=1e6;
    cin >> A >> B >> C;
    a=A, b=B, c=C;
    l=(c-b)/a, r=(b+c)/a;
    int t=100;
    while (t--) {
        x=(l+r)/2;
        if (a*x+b*sine(x)<C)
            l=x;
        else r=x;
    }
    cout << (long double)(Int(r*U+0.5)/U);
}