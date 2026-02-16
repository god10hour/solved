#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

vector<int> bfs(int S, int t, int src) {
    vector<int> dis(S, -1);
    queue<int> q;
    dis[src]=0;
    q.push(src);

    while (!q.empty()) {
        int u=q.front(), v=u^t, w=v+1;
        q.pop();
        if (v<S && dis[v]==-1) dis[v]=dis[u]+1, q.push(v);
        if (w<S && dis[w]==-1) dis[w]=dis[u]+1, q.push(w);
    }
    return dis;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    lint N, M=1LL<<20, x, y, t;
    cin >> N >> x >> y >> t;
    lint hx=x>>20, hy=y>>20, rx=x&M-1, ry=y&M-1;
    if (hx>hy) return !(cout << -1 << '\n');

    lint h_last=(N-1)>>20, S_last=N-M*h_last;
    if (hx==hy) {
        int S=hx==h_last? S_last: M;
        if (rx>=S || ry>=S) return !(cout << -1 << '\n');
        auto dis=bfs(S, t, rx);
        return !(cout << dis[ry] << '\n');
    }

    auto dis0=bfs(M, t, 0);
    auto dis1=bfs(M, t, rx);
    int d0=dis0[t^M-1], d1=dis1[t^M-1];
    if (d1==-1) return !(cout << -1 << '\n');
    int dy=-1;
    if (hy==h_last) {
        if (ry>=S_last) return !(cout << -1 << '\n');
        dy=bfs(S_last, t, 0)[ry];
    }
    else dy=dis0[ry];
    if (dy==-1) return !(cout << -1 << '\n');

    if (hy!=hx+1 && d0==-1) return !(cout << -1 << '\n');
    auto rs=__int128_t(hy-hx-1)*(d0+1)+d1+dy+1;
    cout << lint(rs) << '\n';
}