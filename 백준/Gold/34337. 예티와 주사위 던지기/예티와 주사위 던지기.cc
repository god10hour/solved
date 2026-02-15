#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

static int score(const array<int, 5> &a) {
    array<int, 7> cnt{};
    int s=0;
    bool yacht=true;
    for (int i=0; i<5; i++) cnt[a[i]]++;
    for (int i=1; i<7; i++) s=max(s, i*cnt[i]);
    for (int i=1; i<5; i++) if (a[i]!=a[0]) yacht=false;
    if (yacht) s=max(s, 50);
    return s;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    array<int, 5> d;
    array<lint, 6> pow6{1, };
    for (int i=0; i<5; i++) cin >> d[i];
    for (int i=1; i<6; i++) pow6[i]=pow6[i-1]*6;

    lint r=0;
    for (int k=0; k<32; k++) {
        vector<int> idx;
        for (int i=0; i<5; i++) if (k&1<<i) idx.push_back(i);
        int u=idx.size();
        lint s=0;
        auto cur=d;
        function<void(int)> dfs=[&](int p) {
            if (p==u) {
                s+=score(cur);
                return;
            }
            int pos=idx[p], saved=cur[pos];
            for (int x=1; x<7; x++) {
                cur[pos]=x;
                dfs(p+1);
            }
            cur[pos]=saved;
        };
        dfs(0);
        r=max(r, s*pow6[5-u]);
    }
    cout << r << '\n';
}