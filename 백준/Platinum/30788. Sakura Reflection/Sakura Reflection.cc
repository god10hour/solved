#include <bits/stdc++.h>
using namespace std;
const int MOD=180;

template<size_t N>
bitset<N> rotate(const bitset<N> &b, int s) {
    if (N==0) return b;
    s%=N;
    if (s<0) s+=N;
    if (s==0) return b;
    bitset<N> L=b<<s, R=b>>(N-s);
    return L|R;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i=0; i<n; i++) cin >> v[i];
    if (n%2)
        return !(cout << "NO");
    const int K=n/2;

    static bitset<MOD> dp[502][252];
    dp[0][0].reset();
    dp[0][0].set(0);
    for (int i=0; i<n; i++) {
        int s=v[i];
        for (int j=0; j<=min(i, K); j++) {
            auto now=dp[i][j];
            if (now.none()) continue;
            if (j+1<=K)
                dp[i+1][j+1]|=rotate(now, s);
            dp[i+1][j]|=rotate(now, (MOD-s)%MOD);
        }
    }
    if (!dp[n][K].test(0))
        return !(cout << "NO");

    vector<int> plus, minus;
    plus.reserve(K);
    minus.reserve(K);
    int i=n, k=K, a=0;

    while (i) {
        int s=v[i-1];
        if (k>0) {
            int pre=a-s;
            if (pre<0) pre+=MOD;
            if (dp[i-1][k-1].test(pre)) {
                plus.push_back(i);
                a=pre;
                k--, i--;
                continue;
            }
        }
        int pre=(a+s)%MOD;
        if (dp[i-1][k].test(pre)) {
            minus.push_back(i);
            a=pre;
            i--;
        }
    }
    reverse(plus.begin(), plus.end());
    reverse(minus.begin(), minus.end());
    cout << "YES\n";
    for (int i=0; i<K; i++)
        cout << plus[i] << ' ' << minus[i] << ' ';
}