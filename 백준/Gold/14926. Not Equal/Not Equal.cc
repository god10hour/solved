#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> adj(n+1);
    vector it(n+1, 0);
    vector use(n+1, vector<unsigned char>(n+1, 0));
    vector<int> st, path;
    st.reserve(n*(n-1)/2+1);
    path.reserve(n*(n-1)/2+1);
    st.push_back(1);
    for (int i=1; i<=n; i++) {
        adj[i].reserve(n-1);
        for (int j=1; j<=n; j++) if (i!=j)
            adj[i].push_back(j);
    }
    while (!st.empty()) {
        int v=st.back();
        while (it[v]<adj[v].size() && use[v][adj[v][it[v]]]) it[v]++;

        if (it[v]==adj[v].size()) {
            path.push_back(v);
            st.pop_back();
        }
        else {
            int u=adj[v][it[v]];
            use[v][u]=1;
            use[u][v]=1;
            st.push_back(u);
        }
    }
    ranges::reverse(path);
    for (int i: path)
        cout << 'a' << i << ' ';
}
