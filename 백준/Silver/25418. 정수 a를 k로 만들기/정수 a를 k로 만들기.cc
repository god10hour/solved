#include <bits/stdc++.h>
using namespace std;
const int N=1e6+1;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int s, e;
    vector<int> dis(N, -1);
    queue<int> q;
    cin >> s >> e;
    dis[s]=0;
    q.push(s);
    while (!q.empty()) {
        int u=q.front(); q.pop();
        if (u==e) return !(cout << dis[u]);
        int move[]={u+1, u*2};
        for (int x: move)
            if (x>0 && x<N && dis[x]==-1)
                dis[x]=dis[u]+1, q.push(x);
    }
}