#include <bits/stdc++.h>
using namespace std;

vector<int> get_pi(const string &p) {
    int n=p.size();
    vector<int> pi(n);
    for (int i=1, j=0; i<n; i++) {
        while (j && p[i]!=p[j]) j=pi[j-1];
        if (p[i]==p[j]) j++;
        pi[i]=j;
    }
    return pi;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    string s;
    cin >> s;
    auto pi=get_pi(s);
    int n=s.size(), t=pi[n-1];
    vector<int> r, v(n), c(n, 1);
    for (int i=n-1; i>0; i--) {
        v[i]+=c[i];
        c[pi[i-1]]+=c[i];
    }
    while (t) {
        r.push_back(t);
        t=pi[t-1];
    }
    ranges::sort(r);
    cout << r.size()+1 << '\n';
    for (auto &k: r) cout << k << ' ' << v[k]+1 << '\n';
    cout << n << " 1\n";
}