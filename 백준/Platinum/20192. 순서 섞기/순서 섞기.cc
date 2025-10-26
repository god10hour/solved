#include <bits/stdc++.h>
using namespace std;
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, c=0, r=0;
    cin >> n;
    vector<int> v(n);
    cin >> v[0];
    bool z=1;
    for (int i=1; i<n; i++) {
        cin >> v[i];
        if (v[i-1]>v[i] && z)
            c++, z=0;
        else if (v[i-1]<v[i] && !z)
            z=1;
    }
    if (c && z) c++;
    while (c)
        c=c/2+(c%2 && c>1), r++;
    cout << r;
}