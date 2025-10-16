#include <bits/stdc++.h>
using namespace std;

vector<string> r;
void f(int n, int x, int y) {
    if (n==3) {
        r[x][y]='*';
        r[x+1][y-1]=r[x+1][y+1]='*';
        for (int i=y-2; i<=y+2; i++)
            r[x+2][i]='*';
        return;
    }
    f(n/2, x, y);
    f(n/2, x+n/2, y-n/2);
    f(n/2, x+n/2, y+n/2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    r=vector<string>(n, string(n*2-1, ' '));
    f(n, 0, n-1);
    for (int i=0; i<n; i++)
        cout << r[i] << '\n';
}