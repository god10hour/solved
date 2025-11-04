#include <bits/stdc++.h>
using namespace std;
const int MOD=30011;
const int INV=15006;

int64_t Pow(int64_t n, int64_t k) {
    int64_t r=1;
    while (k) {
        if (k&1)
            r=r*n%MOD;
        n=n*n%MOD;
        k>>=1;
    }
    return r;
}

void FWHT(vector<int> &v, bool inv) {
    int n=v.size();
    for (int k=1; k<=n/2; k*=2)
        for (int i=0; i<n; i+=k*2)
            for (int j=0; j<k; j++) {
                int a=v[i+j], b=v[i+j+k];
                v[i+j]=(a+b)%MOD,
                v[i+j+k]=(a-b+MOD)%MOD;
            }
    if (inv) {
        int64_t ninv=Pow(n, MOD-2);
        for (auto &x: v)
            x=1LL*x*ninv%MOD;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int64_t N, K, s=1;
    cin >> N >> K;

    while (s<K+1) s*=2;
    vector v(s, 0);
    fill(v.begin(), v.begin()+K+1, 1);
    FWHT(v, 0);
    for (int i=0; i<s; i++)
        v[i]=Pow(v[i], N);
    FWHT(v, 1);

    int r=(Pow(K+1, N)-v[0]+MOD)%MOD;
    cout << r;
}