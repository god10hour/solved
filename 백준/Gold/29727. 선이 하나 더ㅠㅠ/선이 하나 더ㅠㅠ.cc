#include <bits/stdc++.h>
using namespace std;

int64_t f(int n, int k) {
    int64_t r=1;
    for (int i=n; i>n-k; i--) r*=i;
    for (int i=k; i>0; i--) r/=i;
    return r;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, x1, y1, x2, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;
    int64_t r=f(n+1, 2)*f(n+1, 2);
    if (x1!=x2 && y1!=y2)
        return !(cout << r);
    if (x1==x2)
        swap(x1, y1),
        swap(x2, y2);
    if (x1>x2) swap(x1, x2);
    if (x1<n && x2>=0) {
        if (x1<0) x1=-1;
        if (x2>n) x2=n;
        r+=f(x2-x1, 2)*(n+1);
    }
    cout << r;
}