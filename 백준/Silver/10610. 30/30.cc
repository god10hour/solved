#include <bits/stdc++.h>
using namespace std;

int main() {
    int r=0;
    string s;
    cin >> s;
    sort(s.begin(), s.end(), greater<char>());
    for (int i=0; i<s.length(); i++)
        r+=s[i]-'0';
    if (r%3 || s.back()!='0')
        return !(cout << -1);
    cout << s;
}