#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    string S, T;
    string s="", t="";
    cin >> S >> T;
    n=S.length(), m=T.length();
    int r=lcm(n, m);
    for (int i=0; i<r/n; i++) s+=S;
    for (int i=0; i<r/m; i++) t+=T;
    cout << (s==t);
}