#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int x, q, m=0;
    cin >> x >> q;
    vector<int> v(q);
    for (int i=0; i<q; i++) {
        cin >> v[i];
        if (m<v[i]) m=v[i];
    }

    int k=sqrt(x*2.0L)+200;
    if (k>m) k=m;
    vector<lint> u(k+1);
    u[0]=x;
    for (int i=1; i<=k; i++)
        u[i]=i*(u[i-1]/i+1);
    lint g=u[k]/k;

    for (int i=0; i<q; i++)
        if (v[i]<=k)
            cout << u[v[i]] << '\n';
        else cout << g*v[i] << '\n';
}