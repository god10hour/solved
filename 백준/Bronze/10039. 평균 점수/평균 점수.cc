#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int s=0;
    for (int i=0; i<5; i++) {
        int k;
        cin >> k;
        s+=max(k, 40);
    }
    cout << s/5 << '\n';
}