#include <bits/stdc++.h>
using namespace std;

template<class F>
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
    int search(const F &s) const {
        int n=s.size(), m=prn.size();
        for (int i=0, j=0; i<n; i++) {
            while (j>0 && s[i]!=prn[j])
                j=pi[j-1];
            if (s[i]==prn[j]) j++;
            if (i==n-1) return j;
            if (j==m) j=pi[m-1];
        }
        return -1;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    string s;
    cin >> n >> s;
    string rev(s.rbegin(), s.rend());
    KMP kmp(rev);
    cout << n-kmp.search(s) << '\n';
}