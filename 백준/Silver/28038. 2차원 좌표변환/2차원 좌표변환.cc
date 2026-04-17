#include <bits/stdc++.h>
using namespace std;
constexpr long double pi=acosl(-1.0L);

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(10);
    int t;
    cin >> t;
    while (t--) {
        int typ;
        long double x, y;
        cin >> typ >> x >> y;

        if (typ==1) {
            long double r=hypotl(x, y);
            long double th=r==0? 0: atan2l(y, x);
            if (th<0) th+=pi*2;
            cout << r << ' ' << th << '\n';
        }
        else {
            long double r=x, th=y;
            cout << r*cosl(th) << ' ' << r*sinl(th) << '\n';
        }
    }
}