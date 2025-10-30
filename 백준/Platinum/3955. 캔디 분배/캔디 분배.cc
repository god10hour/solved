#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int EGCD(int a, int b, int &x, int &y) {
    if (b==0) {
        x=1, y=0;
        return a;
    }
    int d=EGCD(b, a%b, x, y);
    int t=y;
    y=x-a/b*t, x=t;

    if (x<=0) x+=b, y-=a;
    return d;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int k, c, x, y;
        cin >> k >> c;
        if (c==1) {
            if (k<1e9) {
                cout << k+1 << '\n';
                continue;
            }
            cout << "IMPOSSIBLE\n";
            continue;
        }
        if (k==1) {
            cout << 1 << '\n';
            continue;
        }

        int d=EGCD(c, k, x, y);
        if (d!=1) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        while (x>k) x-=k;
        cout << x << '\n';
    }
}