#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

void bfs(vector<int> &dis, int S, lint t, int src) {
    fill_n(dis.begin(), S, -1);
    queue<int> q;
    dis[src]=0;
    q.push(src);

    while (!q.empty()) {
        int u=q.front(), v=u^t, w=v+1;
        q.pop();
        if (v<S && dis[v]==-1) dis[v]=dis[u]+1, q.push(v);
        if (w<S && dis[w]==-1) dis[w]=dis[u]+1, q.push(w);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    lint N, M=1LL<<20, x, y, t;
    cin >> N >> x >> y >> t;
    lint hx=x>>20, hy=y>>20, rx=x&M-1, ry=y&M-1;
    if (hx>hy) return !(cout << -1 << '\n');

    lint h_last=(N-1)>>20, S_last=N-M*h_last;
    vector<int> dis(M);
    if (hx==hy) {
        int S=hx==h_last? S_last: M;
        if (rx>=S || ry>=S) return !(cout << -1 << '\n');
        bfs(dis, S, t, rx);
        return !(cout << dis[ry] << '\n');
    }

    bfs(dis, M, t, 0);
    int d0=dis[t^M-1], dy0=dis[ry];
    bfs(dis, M, t, rx);
    int d1=dis[t^M-1];
    if (d1==-1) return !(cout << -1 << '\n');

    int dy=-1;
    if (hy==h_last) {
        if (ry>=S_last) return !(cout << -1 << '\n');
        bfs(dis, S_last, t, 0);
        dy=dis[ry];
    } else dy=dy0;

    if (dy==-1) return !(cout << -1 << '\n');
    if (hy!=hx+1 && d0==-1) return !(cout << -1 << '\n');
    auto rs=__int128_t(hy-hx-1)*(d0+1)+d1+dy+1;
    cout << lint(rs) << '\n';
    return 0;
}