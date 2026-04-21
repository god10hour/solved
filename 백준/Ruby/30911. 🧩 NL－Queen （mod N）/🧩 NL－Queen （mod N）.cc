#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    if (gcd(n, 6)!=1 || n==5 || n==7 || n==11)
        return !(cout << -1 << '\n');

    int p=0;
    for (int d=5; 1LL*d*d<=n; d+=2)
        if (n%d==0) {
            p=d;
            break;
        }
    vector<int> r(n);

    if (p) {
        for (int x=0; x<n; x++)
            r[x]=(2*x+p*(x/p))%n+1;
    } else {
        p=n;
        vector<bool> resi(p);
        for (int i=1; i<p; i++)
            resi[1LL*i*i%p]=1;

        auto chi=[&](int x) {
            x%=p;
            if (x<0) x+=p;
            if (x==0) return 0;
            return resi[x]? 1: -1;
        };

        int v=-1;
        for (int x=2; x<p-1; x++) {
            if (x==2) continue;
            if (chi(x)==chi(2) && chi(x+1)==chi(3) && chi(1-x)==chi(-1)) {
                v=x;
                break;
            }
        }
        r[0]=1;
        for (int x=1; x<p; x++)
            r[x]=(resi[x]? 2*x: 1LL*v*x)%p+1;
    }

    for (int x: r) cout << x << ' ';
    cout << '\n';
}