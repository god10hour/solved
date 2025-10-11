#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector A(n, vector<int>(m));
    vector<int> r(n), c(m);
    while (q--) {
        int k, i, v;
        cin >> k >> i >> v;
        i--;
        if (k==1)
            r[i]+=v;
        else c[i]+=v;
    }
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            A[i][j]=r[i]+c[j];
    for (int i=0; i<n; i++, cout << '\n')
        for (int j=0; j<m; j++)
            cout << A[i][j] << ' ';
}