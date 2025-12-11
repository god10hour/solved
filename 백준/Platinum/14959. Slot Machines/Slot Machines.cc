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
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i=0; i<n; i++) cin >> v[i];
    ranges::reverse(v);
    KMP kmp(v);
    auto a=kmp.pi;
    int m=ranges::max_element(a)-a.begin(), r=n-m-1;
    cout << r << ' ' << n-(r+a[m]) << '\n';
}