#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const int MOD=1e9+7;

struct Node {
    int lft=1, rgh=1;
    int s=1, v=1;
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<Node> tree(n+1);
    for (int i=1; i<=n; i++) {
        int a, b;
        cin >> a >> b;
        tree[i].v=(tree[a].v+tree[b].v)%MOD;
        tree[i].v=(tree[i].v+tree[a].rgh*tree[b].s+tree[b].lft*tree[a].s-1)%MOD;
        tree[i].s=(tree[a].s+tree[b].s)%MOD;
        tree[i].lft=(tree[a].lft+tree[b].lft+tree[b].s-1)%MOD;
        tree[i].rgh=(tree[a].rgh+tree[b].rgh+tree[a].s-1)%MOD;
        cout << tree[i].v << '\n';
    }
}