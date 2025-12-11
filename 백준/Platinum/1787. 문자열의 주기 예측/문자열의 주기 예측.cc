#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

template <class F>
struct KMP {
    F prn;
    vector<int> pi;
    KMP()=default;
    explicit KMP(const F &p) {
        init(p);
    }

    void init(const F &p) {
        prn=p;
        int m=prn.size();
        pi.assign(m, 0);
        for (int i=1, j=0; i<m; i++) {
            while (j>0 && prn[i]!=prn[j])
                j=pi[j-1];
            if (prn[i]==prn[j]) j++;
            pi[i]=j;
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    lint n, r=0;
    cin >> n >> s;
    KMP kmp(s);
    vector a=kmp.pi;
    vector<lint> dp(n, -1);
    function<lint(int)> f=[&](int k)->lint {
        if (dp[k]!=-1) return dp[k];
        if (!a[k]) return 0LL;
        if (!a[a[k]-1]) return 1LL*k-a[k]+1;
        return dp[k]=f(a[k]-1)+k-a[k]+1;
    };
    for (int i=0; i<n; i++) {
        if (!a[i]) continue;
        r+=f(i);
    }
    cout << r << '\n';
}