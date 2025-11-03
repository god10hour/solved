#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, c=0, s=0;
    string p;
    cin >> n >> p;
    for (int i=0; i<n; i++)
        if (p[i]=='O')
            s+=1+i+c++;
        else c=0;
    cout << s;
}