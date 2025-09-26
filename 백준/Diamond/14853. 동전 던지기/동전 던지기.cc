#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        double n1, m1, n2, m2;
        cin >> n1 >> m1 >> n2 >> m2;
        cout << fixed << setprecision(9);

        double x=1, r;
        for (int i=0; i<=m1; i++)
            x=x*(n1-i+1)/(n1+n2-i+2);
        r=x;
        for (int i=1; i<=m2; i++) {
            x=x*(m1+i)/i * (n2+2-i)/(n1+n2-m1-i+2);
            r+=x;
        }
        cout << r << '\n';
    }
}