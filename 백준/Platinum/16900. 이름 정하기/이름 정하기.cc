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
    vector<int> search(const string &s) {
        vector<int> r;
        if (s.empty()) return r;
        for (int i=0, j=0; i<s.size(); i++) {
            while (j>0 && s[i]!=prn[j])
                j=pi[j-1];
            if (s[i]==prn[j]) j++;
            if (j==prn.size())
                r.push_back(i-j+1), j=pi[j-1];
        }
        return r;
    }
    int count(const string &s) {
        return search(s).size();
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
    string s;
    int n, m;
    cin >> s >> n;
    KMP kmp(s);
    m=s.length();
    cout << 1LL*n*m-1LL*kmp.pi[m-1]*(n-1) << '\n';
}