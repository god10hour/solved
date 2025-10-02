#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, d, s=0;
    cin >> n >> d;
    for (int i=1; i<=n; i++) {
        int k=i;
        while (k) {
            if (k%10==d) s++;
            k/=10;
        }
    }
    cout << s;
}