#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const int LIM=1000000000;
int n, p;
vector<int> prms;

void dfs(int idx, int now, int sign, int M, int &acc) {
    acc+=sign*(M/now);
    for (int i=idx; i<(int)prms.size(); i++) {
        int nxt=now*prms[i];
        if (nxt>M)
            break;
        dfs(i+1, nxt, -sign, M, acc);
    }
}

int rough(int M) {
    if (M<=0) return 0;
    int acc=0;
    dfs(0, 1, 1, M, acc);
    return acc;
}

int cUp(int X) {
    if (X<p) return 0;
    int M=X/p;
    return rough(M);
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> p;
    if (LIM/p<n) {
        cout << 0;
        return 0;
    }

    int lim=min<int>(p-1, LIM/p);
    if (lim>=2) {
        vector<bool> sieve(lim+1, 1);
        sieve[0]=sieve[1]=0;
        for (int i=2; i<=lim; i++)
            if (sieve[i]) {
                prms.push_back(i);
                for (int j=i*i; j<=lim; j+=i)
                    sieve[j]=0;
            }
    }
    int L=p, U=LIM, r=0;
    while (L<=U) {
        int mid=(L+U)/2;
        if (cUp(mid)>=n)
            r=mid,
            U=mid-1;
        else
            L=mid+1;
    }
    cout << (r>LIM? 0:r);
}