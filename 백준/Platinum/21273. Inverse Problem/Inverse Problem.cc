#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr int mod=998244353;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> v(m);
    vector<bool> used(n+1);

    for (auto &x: v) cin >> x, used[x]=true;
    int last=0;
    while (last+1<m && v[last]<v[last+1]) last++;

    int r=1, ptr=0, cnt=0;
    for (int i=1; i<=n; i++) {
        if (used[i]) continue;
        while (ptr<=last && i>v[ptr]) ptr++;
        int ways=ptr;
        if (ptr==last+1) ways++;
        r=lint(r)*(cnt+ways)%mod;
        cnt++;
    }
    cout << r << '\n';
}