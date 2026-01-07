#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, r=0, w=0, h=0;
    cin >> n;
    vector cnt(366, 0);
    for (int i=0; i<n; i++) {
        int a, b;
        cin >> a >> b;
        for (int j=a; j<=b; j++) cnt[j]++;
    }
    for (int i=1; i<366; i++) {
        if (cnt[i]) h=max(h, cnt[i]), w++;
        if (!cnt[i] || i==365) r+=w*h, w=0, h=0;
    }
    cout << r << '\n';
}