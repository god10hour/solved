#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const int N=1e6+5;
int nxt[N], seen[N], dist[N], tme[N];
int cyc_size=-1, st_pt=-1;

void dfs(int i) {
    seen[i]=1;
    if (nxt[i]>=0&&seen[nxt[i]]==2) {
        dist[i]=dist[nxt[i]]+1;
    } else if (seen[nxt[i]]==1||nxt[i]==-1) {
        if (nxt[i]==-1) {
            dist[i]=1;
        } else {
            cyc_size=tme[i]-tme[nxt[i]]+1;
            st_pt=nxt[i];
            dist[i]=cyc_size;
        }
    } else {
        tme[nxt[i]]=tme[i]+1;
        dfs(nxt[i]);
        if (cyc_size!=-1) {
            dist[i]=cyc_size;
            if (st_pt==i) {
                cyc_size=-1;
            }
        } else {
            dist[i]=dist[nxt[i]]+1;
        }
    }
    seen[i]=2;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int M, N;
    cin>>M>>N;
    memset(nxt, -1, sizeof nxt);
    for (int i=0; i<M; i++) {
        int u, v;
        cin>>u>>v;
        nxt[u]=v;
    }
    int ans=0;
    vector<int> stk;
    for (int i=0; i<N; i++) {
        if (seen[i])
            continue;
        cyc_size=-1;
        dfs(i);
        ans=max(ans, dist[i]);
    }
    cout<<ans;
}
