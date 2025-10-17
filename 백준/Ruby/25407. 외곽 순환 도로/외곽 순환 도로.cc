#include <bits/stdc++.h>
using namespace std;
using Int=int64_t;
const int N=3e5;
const Int INF=1e18;

vector<pair<int, Int>> g[N], g2[N];
Int r[N], dis[N];
int T=0, use[N], siz[N], comp[N], was[N];

void get(int v, int p) {
    siz[v]=1;
    for (auto &[u, w]: g[v])
        if (u!=p && !use[u]) {
            get(u, v);
            siz[v]+=siz[u];
        }
}

int centroid(int v, int p, int s) {
    for (auto &[u, w]: g[v])
        if (u!=p && !use[u] && siz[u]>=(s+1)/2)
            return centroid(u, v, s);
    return v;
}

vector<int> t;
void dfs(int v, int p, int c) {
    comp[v]=c;
    t.push_back(v);
    was[v]=T;
    for (auto &[u, w]: g[v])
        if (u!=p && !use[u])
            dfs(u, v, c);
}

void update(int s, const vector<array<int, 3>> &qu) {
    for (auto &u: t) dis[u]=INF;
    dis[s]=0;
    priority_queue<pair<Int, int>, vector<pair<Int, int>>, greater<>> q;
    q.push({0, s});
    while (!q.empty()) {
        auto [d, v]=q.top();
        q.pop();
        if (dis[v]!=d) continue;
        for (auto &[u, w]: g2[v])
            if (was[u]==T && dis[u]>d+w) {
                dis[u]=d+w;
                q.push({d+w, u});
            }
    }
    for (auto &[x, y, i]: qu)
        r[i]=min(r[i], dis[x]+dis[y]);
}

void run(int v, vector<array<int, 3>> qu) {
    get(v, v);
    v=centroid(v, v, siz[v]);
    int c=0;
    comp[v]=c++;
    t={v};
    was[v]=++T;
    vector<int> wan={v};
    for (auto &[u, w]: g[v])
        if (!use[u])
            dfs(u, v, c++);
    for (auto &x: t)
        for (auto &[u, w]: g2[x])
            if (!use[u] && was[u]==T &&
                comp[u] && comp[x] &&
                comp[u]!=comp[x]) {
                wan.push_back(min(u, x));
                break;
            }
    sort(wan.begin(), wan.end());
    wan.erase(unique(wan.begin(), wan.end()), wan.end());
    for (auto &x: wan) update(x, qu);
    use[v]=1;
    vector<vector<array<int, 3>>> nq;
    for (auto& [u, w] : g[v])
        if (!use[u]) {
            nq.push_back({});
            for (auto &[x, y, _]: qu)
                if (comp[x]==comp[y] && comp[x]==comp[u])
                    nq.back().push_back({x, y, _});
        }
    reverse(nq.begin(), nq.end());
    for (auto &[u, w]: g[v])
        if (!use[u]) {
            run(u, nq.back());
            nq.pop_back();
        }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n;
    vector<set<pair<int, Int>>> G(n*2);
    for (int i=1; i<n; i++) {
        int p;
        Int w;
        cin >> p >> w;
        p--;
        G[i].insert({p, w});
        G[p].insert({i, w});
    }
    vector<int> leaves;

    int o=n;
    auto dfs=[&](auto &&dfs, int v, int p) ->void {
        vector<pair<int, Int>> S;
        for (auto &[u, w]: G[v])
            if (u!=p) {
                S.push_back({u, w});
                dfs(dfs, u, v);
            }
        if (S.empty()) leaves.push_back(v);
        while (S.size()>2) {
            auto [x, xw]=S.back();
            S.pop_back();
            auto [y, yw]=S.back();
            S.pop_back();
            if (x<o) {
                G[v].erase({x, xw});
                G[x].erase({v, xw});
            }
            if (y<o) {
                G[v].erase({y, yw});
                G[y].erase({v, yw});
            }
            G[n].insert({x, xw});
            G[n].insert({y, yw});
            G[x].insert({n, xw});
            G[y].insert({n, yw});
            S.push_back({n, 0});
            n++;
        }
        for (auto &[x, xw]: S) {
            G[v].insert({x, xw});
            G[x].insert({v, xw});
        }
    };
    dfs(dfs, 0, 0);

    for (int i=0; i<n; i++)
        for (auto &[u, w]: G[i])
            g[i].push_back({u, w}),
            g2[i].push_back({u, w});
    for (int i=0, l=leaves.size(); i<l; i++) {
        int v=leaves[i], u=leaves[(i+1)%l];
        Int k;
        cin >> k;
        g2[v].push_back({u, k});
        g2[u].push_back({v, k});
    }

    cin >> q;
    vector<array<int, 3>> qu(q);
    for (int i=0; i<q; i++) {
        cin >> qu[i][0] >> qu[i][1];
        qu[i][2]=i;
        qu[i][0]--, qu[i][1]--;
    }
    fill (r, r+q, INF);
    run(0, qu);
    for (int i=0; i<q; i++)
        cout << r[i] << '\n';
}