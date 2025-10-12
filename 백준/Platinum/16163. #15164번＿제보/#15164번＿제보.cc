#include <bits/stdc++.h>
#define int int64_t
using namespace std;

vector<int> manacher(string s, int n) {
    int p=0, r=0;
    vector<int> v(n);
    for (int i=0; i<n; i++) {
        if (i<=r)
            v[i]=min(v[p*2-i], r-i);
        else v[i]=0;
        while (i-v[i]>0 && i+v[i]<n-1 && s[i-v[i]-1]==s[i+v[i]+1])
            v[i]++;
        if (r<i+v[i])
            r=i+v[i], p=i;
    }
    return v;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    string s, t;
    cin >> t;
    for (int i=0; i<t.length(); i++)
        s+='.', s+=t[i];
    s+='.';
    auto v=manacher(s, s.length());
    int r=0;
    for (int i=0; i<s.size(); i++)
        r+=(v[i]+1)/2;
    cout << r;
}