#include <bits/stdc++.h>
using namespace std;

string s;
bool con(int l, int r) {
    if (l==r) return 1;
    int x=l, y=r;
    while (x!=y)
        if (s[x++]==s[y--])
            return 0;
    return con(l, r/2-1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> s;
        cout <<(con(0, s.size()-1)? "YES": "NO") << '\n';
    }
}