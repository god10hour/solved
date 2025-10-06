#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    for (int x=-999; x<1000; x++)
        for (int y=-999; y<1000; y++)
            if (a*x+b*y==c)
                if (d*x+e*y==f)
                    return !(cout << x << ' ' << y);
}