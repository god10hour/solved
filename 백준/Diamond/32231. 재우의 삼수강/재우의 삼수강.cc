#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);

    int T;
    cin >> T;
    while (T--) {
        long double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        long double dx=x1-x2, dy=y1-y2;
        long double d=hypotl(dx, dy);
        long double r=2.0L*asinhl(d/(2.0L*sqrtl(y1*y2)));
        cout << r << '\n';
    }
}