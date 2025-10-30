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
    int n, a, x, y;
    cin >> n >> a;
    int d=EGCD(a, n, x, y);
    cout << n-a << ' ';
    cout << (d==1? x: -1);
}