#include <bits/stdc++.h>
using namespace std;

int cost(const vector<vector<int>> &g) {
    int n=g.size();
    vector<int> u(n+1), v(n+1), p(n+1);
    vector<int> way(n+1);

    for (int i=1; i<=n; i++) {
        p[0]=i;
        int c=0;
        vector<int> w(n+1, 1e9);
        vector<bool> use(n+1, 0);
        while (p[c]) {
            use[c]=1;
            int idx=p[c], nc=0, del=1e9;
            for (int j=1; j<=n; j++)
                if (!use[j]) {
                    int now=g[idx-1][j-1]-u[idx]-v[j];
                    if (now<w[j]) {
                        w[j]=now;
                        way[j]=c;
                    }
                    if (w[j]<del) {
                        del=w[j];
                        nc=j;
                    }
                }
            for (int j=0; j<=n; j++)
                if (use[j])
                    u[p[j]]+=del, v[j]-=del;
                else w[j]-=del;
            c=nc;
        }
        do {
            int j1=way[c];
            p[c]=p[j1];
            c=j1;
        } while (c);
    }
    int r=0;
    for (int i=1; i<=n; i++)
        r+=g[p[i]-1][i-1];
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            cin >> g[i][j];
    cout << cost(g);
}