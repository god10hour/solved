#include <bits/stdc++.h>
using namespace std;

array<int, 10'000'000> a;
int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--) {
        int t;
        cin >> t;
        if (a[t]) return !(cout << t << '\n');
        a[t]++;
    }
}