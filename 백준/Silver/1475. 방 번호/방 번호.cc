#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n=0;
    string s;
    vector<int> v(9, 0);
    cin >> s;
    for (char c: s)
        v[c=='9'? 6:c-'0']++;
    v[6]=(v[6]+1)/2;
    for (int x: v)
        n=max(n, x);
    cout << n;
}