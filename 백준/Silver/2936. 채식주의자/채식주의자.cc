#include <bits/stdc++.h>
using namespace std;

const double s=31250.0, l=125.0;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    double x, y;
    cin >> x >> y;
    double rx=0.0, ry=0.0;
    if (x==0)
        if (y==0)
            rx=ry=l;
        else if (y<l)
            rx=s/(250.0-y),
            ry=250.0-rx;
        else rx=s/y;
    else if (y==0)
        if (x<l)
            ry=s/(250.0-x),
            rx=250.0-ry;
        else ry=s/x;
    else
        if (x<l)
            rx=250.0-s/y;
        else ry=250.0-s/x;

    cout << fixed << setprecision(2) << rx << ' ' << ry << '\n';
}