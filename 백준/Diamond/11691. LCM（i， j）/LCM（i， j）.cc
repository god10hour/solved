#include <bits/stdc++.h>
using namespace std;
const int N=1e6+1;
const int MOD=1e9+7;
const int INV2=(MOD+1)/2;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<int> phi(N);
    vector<int64_t> v(N);
    iota(phi.begin(), phi.end(), 0);
    for (int i=2; i<N; i+=2) phi[i]/=2;
    for (int i=3; i<N; i+=2)
        if (i==phi[i])
            for (int j=i; j<N; j+=i)
                phi[j]-=phi[j]/i;
    for (int i=1; i<N; i++)
        for (int j=i; j<N; j+=i)
            v[j]+=int64_t(i)*phi[i], v[j]%=MOD;
    for (int i=1; i<N; i++)
        v[i]=(v[i-1]+(v[i]-1)*INV2%MOD*i)%MOD;

    int n;
    cin >> n;
    cout << v[n];
}