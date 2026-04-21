#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int n;
    cin >> n;
    vector<long double> rs(n);
    for (auto &x: rs) cin >> x;
    const long double pi=acosl(-1.0L);

    long double l=0, r=2000;
    for (int i=0; i<70; i++) {
        long double mid=(l+r)/2, s=0;
        for (auto x: rs) if (x>mid) s+=acosl(mid/x);
        (s>pi? l: r)=mid;
    }
    long double x=(l+r)/2, s=0;

    for (auto ri: rs) {
        if (ri<=x) continue;
        long double ang=acosl(x/ri);
        s+=ri*ri*(ang*2+sinl(ang*2));
    }
    cout << s << '\n';
}