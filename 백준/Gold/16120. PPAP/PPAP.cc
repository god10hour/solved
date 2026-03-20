#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s, v;
    cin >> s;
    for (const char &c: s) {
        if (c!='A' && c!='P') return !(cout << "NP");
        v+=c;
        int n=v.size();
        if (n>3 && v.substr(n-4)=="PPAP")
            for (int i=0; i<3; i++) v.pop_back();
    }
    cout << (v.size()==1 && v[0]=='P'? "PPAP": "NP") << '\n';
}