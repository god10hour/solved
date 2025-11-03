#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string a, b;
    cin >> a >> b;
    int n=a.length();
    for (int i=0; i<n; i++)
        cout << (a[i]=='1' && b[i]=='1');
    cout << '\n';
    for (int i=0; i<n; i++)
        cout << (a[i]=='1' || b[i]=='1');
    cout << '\n';
    for (int i=0; i<n; i++)
        cout << (a[i]!=b[i]);
    cout << '\n';
    for (int i=0; i<n; i++)
        cout << (a[i]!='1');
    cout << '\n';
    for (int i=0; i<n; i++)
        cout << (b[i]!='1');
}