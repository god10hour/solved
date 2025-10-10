#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, s=0;
        cin >> n;
        while (n>1) {
            if (n%2)
                n++;
            else n/=2;
            s++;
        }
        cout << s << '\n';
    }
}
