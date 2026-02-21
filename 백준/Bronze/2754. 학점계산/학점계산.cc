#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    string s;
    cin >> s;
    if (s[0] == 'F') return !(cout << "0.0" << '\n');
    int i=('A'-s[0]+4)*10;
    if (s[1]=='+') i+=3;
    if (s[1]=='-') i-=3;
    cout << i/10 << '.' << i%10 << '\n';
}