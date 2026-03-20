#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s, t;
    cin >> s >> t;
    while (t.size()>s.size())
        if (t.back()=='A')
            t.pop_back();
        else {
            t.pop_back();
            ranges::reverse(t);
        }
    cout << (s==t) << '\n';
}
