#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, x, y, r=0;
    char d;
    cin >> n;
    vector<int> X(n), Y(n);
    for (int i=0; i<n; i++)
        cin >> X[i] >> Y[i];
    cin >> x >> y >> d;

    if (d=='E') {
        sort(X.begin(), X.end());
        for (int i=0; i<n; i++)
            r+=llabs(Y[i]-y)+llabs(X[i]-x-i);
    }
    else {
        sort(Y.begin(), Y.end());
        for (int i=0; i<n; i++)
            r+=llabs(X[i]-x)+llabs(Y[i]-y-i);
    }
    cout << r;
}