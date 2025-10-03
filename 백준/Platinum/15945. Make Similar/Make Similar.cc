#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    bool pos=0, neg=0;
    cin >> n;
    vector<int> v;
    for (int i=0; i<n; i++) {
        cin >> k;
        if (k) v.push_back(k);
        if (k>0) pos=1;
        if (k<0) neg=1;
    }
    if (pos==neg)
        return !(cout << 0);
    sort(v.begin(), v.end());
    cout << min(
        pos? v.front(): -v.back(),
        v.back()-v.front()
        );
}