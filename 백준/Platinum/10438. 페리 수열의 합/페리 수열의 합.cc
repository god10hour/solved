#include <bits/stdc++.h>
using namespace std;
const int N=10001;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<int> phi(N);
    iota(phi.begin(), phi.end(), 0);
    for (int i=2; i<N; i++)
        if (i==phi[i])
            for (int j=i; j<N; j+=i)
                phi[j]=phi[j]/i*(i-1);
    for (int i=2; i<N; i++)
        phi[i]=phi[i-1]+phi[i]*3;

    int t;
    cin >> t;
    for (int i=1; i<=t; i++) {
        int n;
        cin >> n >> n;
        if (n==1) {
            cout << i << " 1\n";
            continue;
        }
        cout << i << ' ' << phi[n]+1 << "/2\n";
    }
}