#include <bits/stdc++.h>
using namespace std;

struct KMP {
    string prn;
    vector<int> pi;
    KMP()=default;
    explicit KMP(const string &p) {
        init(p);
    }

    void init(const string &p) {
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
    bool contains(const string &s) {
        if (prn.empty()) return 1;
        for (int i=0, j=0; i<s.size(); i++) {
            while (j>0 && s[i]!=prn[j])
                j=pi[j-1];
            if (s[i]==prn[j]) j++;
            if (j==prn.size())
                return 1;
        }
        return 0;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string p, s;
    cin >> p >> s;
    KMP kmp(s);
    cout << kmp.contains(p) << '\n';
}