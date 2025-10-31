#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const int D=11;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);

    int n=1, q;
    vector<int> dim(D), stride(D, 1);;
    for (int i=0; i<D; i++) cin >> dim[i];
    for (int i=0; i<D; i++) n*=dim[i];
    for (int i=D-2; i>=0; i--) stride[i]=stride[i+1]*dim[i+1];
    vector<int> a(n);
    for (int i=0; i<n; i++) cin >> a[i];

    for (int d=0; d<D; d++) {
        int sd=stride[d];
        for (int i=0; i<n; i++)
            if (i/sd%dim[d]>0)
                a[i]+=a[i-sd];
    }

    cin >> q;
    while (q--) {
        array<int, D> L{}, R{};
        for (int d=0; d<D; d++) cin >> L[d];
        for (int d=0; d<D; d++) cin >> R[d];

        int r=0;
        for (unsigned k=0; k<(1<<D); k++) {
            array<int, D> C{};
            bool zero=0;
            for (int d=0; d<D; d++) {
                if (k&(1<<d)) {
                    if (L[d]<=1) {
                        zero=1;
                        break;
                    }
                    C[d]=L[d]-1;
                }
                else C[d]=R[d];
            }
            if (zero) continue;

            int idx=0;
            for (int d=0; d<D; d++) idx+=(C[d]-1)*stride[d];
            if (__builtin_popcount(k)&1)
                r-=a[idx];
            else r+=a[idx];
        }
        cout << r << '\n';
    }
}