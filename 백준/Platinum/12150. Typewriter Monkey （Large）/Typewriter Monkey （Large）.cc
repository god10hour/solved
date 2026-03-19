#include <bits/stdc++.h>
using namespace std;

double remaining_bananas(
    int K, int L, int S,
    const string &key,
    const string &tar
) {
    if (L>S) return 0.0;
    unordered_map<char, int> freq;
    for (const char &k: key) freq[k]++;
    for (const char &k: tar) if (!freq.contains(k)) return 0.0;

    int spa=-1;
    for (int i=1; i<=L; i++)
        if (tar.substr(i)==tar.substr(0, L-i)) {
            spa=i; break;
        }
    if (spa<0) spa=L;
    int ideal=(S-L)/spa+1;

    unordered_map<char, double> prob;
    for (const auto &[k, v]: freq)
        prob[k]=double(v)/K;
    if (L==1) return ideal-S*prob[tar[0]];

    double expect=0.0;
    vector<double> dp(L-1, 0.0);
    for (int i=0; i<S; i++) {
        expect+=dp[L-2]*prob[tar[L-1]];
        for (int j=L-2; j>=1; j--)
            dp[j]=dp[j-1]*prob[tar[j]];
        dp[0]=prob[tar[0]];
    }
    return ideal-expect;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(10);
    int T;
    cin >> T;
    for (int t=1; t<=T; t++) {
        int K, L, S;
        string key, tar;
        cin >> K >> L >> S;
        cin >> key >> tar;
        cout << "Case #" << t << ": "
             << remaining_bananas(K, L, S, key, tar) << '\n';
    }
}