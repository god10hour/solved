#include <bits/stdc++.h>
using namespace std;

struct DP {
    string n, a, b;
    int LA, LB, LN;
    // dp[pos][tight][started][i][j][L]=count
    // pos: 0..LN, i: 0..LA, j: 0..LB, L: 0..LN
    int64_t dp[20][2][2][20][20][20];
    bool vis[20][2][2][20][20][20];
    int nxtA[20][10], nxtB[20][10];

    int64_t go(int pos, bool tig, int sta, int i, int j, int L) {
        if (pos==LN) {
            if (sta && i==LA && j==LB && L>=max(LA, LB)+1)
                return 1;
            return 0;
        }
        if (vis[pos][tig][sta][i][j][L])
            return dp[pos][tig][sta][i][j][L];
        vis[pos][tig][sta][i][j][L]=1;
        auto &r=dp[pos][tig][sta][i][j][L]=0;

        int limit=tig? n[pos]-'0': 9;
        for (int d=0; d<=limit; d++) {
            if (!sta && d==0)
                r+=go(pos+1, tig && d==limit, 0, i, j, L);
            else
                r+=go(pos+1, tig && d==limit, 1, nxtA[i][d], nxtB[j][d], L+1);
        }
        return r;
    }

    int64_t run(int64_t N, int64_t A, int64_t B) {
        n=to_string(N);
        a=to_string(A);
        b=to_string(B);
        LA=a.length();
        LB=b.length();
        LN=n.length();

        for (int i=0; i<=LA; i++)
            for (int d=0; d<10; d++)
                if (i<LA && a[i]-'0'==d)
                    nxtA[i][d]=i+1;
                else
                    nxtA[i][d]=i;
        for (int j=0; j<=LB; j++)
            for (int d=0; d<10; d++)
                if (j<LB && b[j]-'0'==d)
                    nxtB[j][d]=j+1;
                else
                    nxtB[j][d]=j;
        memset(vis, 0, sizeof vis);
        return go(0, 1, 0, 0, 0, 0);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    static DP s;
    cin >> t;
    while (t--) {
        int64_t N, A, B;
        cin >> N >> A >> B;
        cout << s.run(N, A, B) << '\n';
    }
}