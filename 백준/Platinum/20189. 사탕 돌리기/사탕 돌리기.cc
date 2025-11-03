#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    int64_t q, s=0;
    bool z=1;
    cin >> n >> k >> q;

    for (int i=1; i<=n; i++)
        for (int j=0; j<k; j++) {
            int c, d;
            cin >> c;
            d=c-i;
            if (d<0) d+=(-d+n-1)/n*n;
            d%=n;
            s+=d;
            if (i==1 && c!=1) z=0;
        }

    int64_t Q=(s+n-1)/n;
    if (z && s%n==0) Q++;
    cout << (q>=Q) << '\n';
}