#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int dr[]={-2, -2, 0, 0, 2, 2};
    int dc[]={-1, 1, -2, 2, -1, 1};
    int n, r1, c1, r2, c2;
    deque<pair<int, int>> q;
    cin >> n >> r1 >> c1 >> r2 >> c2;
    vector v(n, vector(n, -1));
    q.push_back({r1, c1});
    v[r1][c1]=0;
    while (!q.empty()) {
        auto [x, y]=q.front();
        q.pop_front();
        if (x==r2 && y==c2) break;
        for (int k=0; k<6; k++) {
            int nx=x+dr[k], ny=y+dc[k];
            if (nx>=0 && nx<n && ny>=0 && ny<n && v[nx][ny]==-1)
                q.push_back({nx, ny}), v[nx][ny]=v[x][y]+1;
        }
    }
    cout << v[r2][c2] << '\n';
}