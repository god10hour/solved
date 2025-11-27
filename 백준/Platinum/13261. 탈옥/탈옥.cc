#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr lint inf=1e18;

// dp[t][i]=min_{0<=k<=i}(dp[t-1][k]+C[k][i])
template<class F>
void dnc(
    int l, int r, int pl, int pr,
    const vector<lint> &pre, vector<lint> &cur,
    const F &cost, int g
) {
    if (l>r) return;
    int mid=(l+r)/2;
    lint opt=inf, arg=-1;

    int s=max(pl, g-1), e=min(mid-1, pr);
    for (int k=s; k<=e; k++) {
        lint cand=pre[k]+cost(k, mid);
        if (cand<opt)
            opt=cand, arg=k;
    }
    cur[mid]=opt;

    if (l==r) return;
    dnc(l, mid-1, pl, arg, pre, cur, cost, g);
    dnc(mid+1, r, arg, pr, pre, cur, cost, g);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int L, G;
    cin >> L >> G;
    vector<lint> C(L+1), S(L+1);
    vector<lint> pre(L+1, inf), cur(L+1, inf);
    for (int i=1; i<=L; i++) cin >> C[i];
    for (int i=1; i<=L; i++) S[i]=S[i-1]+C[i];
    int K=min(L, G);
    pre[0]=0;

    auto cost=[&](int k, int i) {
        return 1LL*(i-k)*(S[i]-S[k]);
    };
    for (int k=1; k<=K; k++) {
        dnc(k, L, k-1, L-1, pre, cur, cost, k);
        fill_n(cur.begin(), k, inf);
        pre.swap(cur);
    }
    cout << pre[L] << '\n';
}