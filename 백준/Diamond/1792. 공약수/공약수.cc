#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr int N=50001;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    bitset<N> sieve;
    vector<int> prime;
    vector lp(N, 0), mu(N, 0);
    mu[1]=1;
    for (int i=2; i<N; i++) {
        if (lp[i]==0) {
            lp[i]=i;
            sieve.set(i);
            prime.push_back(i);
            mu[i]=-1;
        }
        for (int p: prime) {
            lint v=1LL*i*p;
            if (v>=N) break;
            lp[v]=p;
            if (p==lp[i]) {
                mu[v]=0;
                break;
            }
            mu[v]=-mu[i];
        }
    }

    vector<lint> pre(N, 0);
    for (int i=1; i<N; i++) pre[i]=pre[i-1]+mu[i];
    auto coprime=[&](int a, int b)->lint {
        if (a>b) swap(a, b);
        lint rs=0;
        for (int l=1; l<=a;) {
            int a1=a/l, b1=b/l;
            int r=min({a, a/a1, b/b1});
            rs+=1LL*(pre[r]-pre[l-1])*a1*b1;
            l=r+1;
        }
        return rs;
    };
    int n;
    cin >> n;
    while (n--) {
        int a, b, d;
        cin >> a >> b >> d;
        cout << coprime(a/d, b/d) << '\n';
    }
}