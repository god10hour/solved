#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> v;
int f(int n, int x, int y) {
    if (n==1) return v[x][y];
    array<int, 4> a;
    a[0]=f(n/2, x, y);
    a[1]=f(n/2, x+n/2, y);
    a[2]=f(n/2, x, y+n/2);
    a[3]=f(n/2, x+n/2, y+n/2);
    sort(a.begin(), a.end());
    return a[1];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    v.assign(n, vector(n, 0));
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            cin >> v[i][j];
    cout << f(n, 0, 0);
}