#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    string s, r;
    getline(cin, s);
    for (int i=0, j=0; i<s.size(); i=j)
        if (s[i]=='<') {
            while (j<s.size() && s[j]!='>') j++;
            r+=s.substr(i, ++j-i);
        } else {
            while (j<s.size() && s[j]!=' ' && s[j]!='<') j++;
            auto t=s.substr(i, j-i);
            ranges::reverse(t);
            r+=t;
            if (s[j]==' ') r+=' ', j++;
        }
    cout << r << '\n';
}