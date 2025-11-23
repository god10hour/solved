#include <bits/stdc++.h>
using namespace std;

// General Matching: Edmonds Blossom, O(V^3)
struct Blossom {
    int n=0;
    vector<vector<int>> g;
    vector<int> match, p, base;
    vector<bool> used, blos;
    queue<int> q;

    explicit Blossom(int n): n(n), g(n) {
        match.assign(n, -1);
        base.resize(n);
        used.resize(n);
        blos.resize(n);
    }

    void add(int u, int v) {
        if (u==v) return;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int lca(int a, int b) {
        vector<bool> path(n, false);
        while (1) {
            a=base[a];
            path[a]=true;
            if (match[a]==-1) break;
            a=p[match[a]];
        }
        while (1) {
            b=base[b];
            if (path[b]) return b;
            if (match[b]==-1) break;
            b=p[match[b]];
        }
        return -1;
    }

    void mark(int v, int b, int child) {
        while (base[v]!=b) {
            blos[base[v]]=blos[base[match[v]]]=true;
            p[v]=child;
            child=match[v];
            v=p[match[v]];
        }
    }

    bool find(int root) {
        used.assign(n, false);
        p.assign(n, -1);
        for (int i=0; i<n; i++) base[i]=i;
        while (!q.empty()) q.pop();
        used[root]=true;
        q.push(root);

        while (!q.empty()) {
            int v=q.front(); q.pop();
            for (int u: g[v]) {
                if (base[v]==base[u] || match[v]==u)
                    continue;
                if (u==root || (match[u]!=-1 && p[match[u]]!=-1)) {
                    int cur=lca(v, u);
                    blos.assign(n, false);
                    mark(v, cur, u);
                    mark(u, cur, v);
                    for (int i=0; i<n; i++)
                        if (blos[base[i]]) {
                            base[i]=cur;
                            if (!used[i]) used[i]=true, q.push(i);
                        }
                }

                else if (p[u]==-1) {
                    p[u]=v;
                    if (match[u]==-1) {
                        int cur=u;
                        while (cur!=-1) {
                            int pv=p[cur];
                            int nv=pv==-1? -1: match[pv];
                            match[cur]=pv;
                            if (pv!=-1) match[pv]=cur;
                            cur=nv;
                        }
                        return true;
                    }
                    int w=match[u];
                    if (!used[w]) used[w]=true, q.push(w);
                }
            }
        }
        return false;
    }

    int max() {
        int m=0;
        match.assign(n, -1);
        for (int i=0; i<n; i++)
            if (match[i]==-1)
                if (find(i))
                    m++;
        return m;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    Blossom GM(n);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        GM.add(u-1, v-1);
    }

    cout << GM.max() << '\n';
}