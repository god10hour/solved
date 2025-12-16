#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, c=0, fir=0, las=0;
        bool all=true;
        cin >> n;
        vector<int> v(n+1), p(n+1);
        for (int i=1; i<=n; i++) {
            cin >> v[i];
            if (v[i]==3) {
                c++;
                if (!fir) fir=i;
                las=i;
            }
            else all=false;
            p[i]=p[i-1]^v[i];
        }
        if (c==0) {
            cout << 0 << '\n';
            continue;
        }
        if (n==1) {
            cout << -1 << '\n';
            continue;
        }
        if (all) {
            cout << (n%2? 3: 1) << '\n';
            continue;
        }

        bitset<4> L, R;
        for (int i=0; i<fir; i++) L[p[i]]=1;
        for (int i=las; i<=n; i++) R[p[i]]=1;
        bool z=false;
        for (int x=0; x<4; x++) if (L[x])
            for (int y=0; y<4; y++) if (R[y] && y!=(x^3)) z=true;
        cout << (z? 1 : 2) << '\n';
    }
}