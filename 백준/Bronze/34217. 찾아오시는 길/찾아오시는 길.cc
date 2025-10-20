#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    if (a+c==b+d)
        cout << "Either";
    else cout << (a+c<b+d? "Hanyang Univ.": "Yongdap");
}