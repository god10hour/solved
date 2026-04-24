#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

bool odd_binom(lint n, lint k) {
    if (k<0 || k>n) return false;
    return (k&~n)==0;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<bitset<2000>> adj(n);
    vector<int> deg(n);
    vector<pair<int, int>> edges;

    for (int i=0; i<n-1; i++) {
        string s;
        cin >> s;
        for (int j=0; j<s.size(); j++) {
            if (s[j]=='0') continue;
            int u=i, v=i+j+1;
            adj[u][v]=adj[v][u]=true;
            deg[u]++, deg[v]++;
            edges.emplace_back(u, v);
        }
    }

    int m=edges.size(), r=0;

    r^=odd_binom(n, 4);
    if (m&1 && odd_binom(n-2, 2)) r^=1;
    int path=0, star=0;
    for (int d: deg) {
        path^=odd_binom(d, 2);
        star^=odd_binom(d, 3);
    }

    if (path && n-3&1) r^=1;
    r^=path^odd_binom(m, 2);
    r^=star;

    int path3=0;
    for (auto [u, v]: edges) {
        int common=(adj[u]&adj[v]).count()&1;
        int term=(deg[u]-1&1)&(deg[v]-1&1);
        path3^=term^common;
    }
    r^=path3;
    cout << r << '\n';
}