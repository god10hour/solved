#include <bits/stdc++.h>
using namespace std;
const int N=1e6+1;

int64_t f(int64_t n) {
    return n*(n-1)*(n-2)/6;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, x;
    int64_t r=0;
    cin >> n;
    vector<int> C(N, 0), mu(N, 0);
    mu[1]=1;
    for (int i=0; i<n; i++) cin >> x, C[x]++;
    for (int i=1; i<N; i++)
        for (int j=i*2; j<N; j+=i)
            C[i]+=C[j], mu[j]-=mu[i];
    for (int i=1; i<N; i++) r+=mu[i]*f(C[i]);
    cout << r;
}