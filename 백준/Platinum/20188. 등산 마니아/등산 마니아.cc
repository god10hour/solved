#include <bits/stdc++.h>
using namespace std;
int n;
int64_t r;
vector<vector<int>> g;

int dfs(int u, int par) {
    int a=1;
    for (int i: g[u]) {
        if (i!=par) {
            int64_t c=dfs(i, u), k=n-c;
            r+=c*k+c*(c-1)/2;
            a+=c;
        }
    }
    return a;
}

int main() {
    cin >> n;
    g.resize(n+1);
    for (int i=0; i<n-1; i++) {
        int v, u;
        cin >> v >> u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    dfs(1, 1);
    cout << r;
}