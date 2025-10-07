#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int S, Q;
map<array<int, 3>,int> dp;
int dfs(int a1, int b1, int a2, int b2) {
    if (a1>=a2 && b1>=b2) return 1;
    if (a1+b1*S<=0 || (a1<=0 && a2>=S) || b1<0) return 0;
    if (a2+b2*S<=0 || (a1>=S && a2<=S) || b2<0) return 1;

    int z=0;
    while (1) {
        if (a1<=0 && a2<=0) {
            int k=min(-a1/S+1, -a2/S+1);
            k=min(k, min(b1, b2));
            if (k) {
                b1-=k, b2-=k;
                a1+=k*S, a2+=k*S;
                continue;
            }
        }
        if ((a1>=a2 && b1>=b2) ||
            (a1+b1*S>=a2+b2*S && b1<b2)) return z^1;
        if (a1+b1*S<=0 || (a1<=0 && a2>=S) || b1<0) return z;
        if (a2+b2*S<=0 || (a1>=S && a2<=S) || b2<0) return z^1;
        
        if (a1<=0) {
            if (!b2) {
                int k=-a1/(S-a2)+1;
                if (k>b1) return z;
                a1+=(S-a2)*k;
                b1-=k;
                continue;
            }
            z^=1;
            a1+=S, b1--;;
            swap(a1, a2), swap(b1, b2);
            continue;
        }
        if (a2<=0 && !b1) {
            z^=1;
            a2-=a1;
            swap(a1, a2), swap(b1, b2);
            continue;
        }
        if (a2<=0 && b1>0) {
            z^=1;
            a1+=S, b1--;
            swap(a1, a2), swap(b1, b2);
            continue;
        }
        if (a2>=S) {
            z^=1;
            a2-=a1;
            swap(a1, a2), swap(b1, b2);
            continue;
        }
        if (a1+(S-a2)*b1>=S) return z^1;
        if (a2-(a1+b1*(S-a2))+b2*(S-a1-b1*(S-a2))>=S) return z;
        
        int k=min(b1, (b2*(S-a1)+a2-a1-S)/(S-a2)/(b2+1));
        if (k>0) a1+=(S-a2)*k, b1-=k;
        break;
    }
    
    __int128 w=b1>>1;
    w*=b1-w;
    if (w>=S*2) return z^1;
    w*=b2+1;
    if (w>=S*2) return z^1;
    w*=S-a2;
    if (w>=S*2) return z^1;
    
    if (!dp.count({b1, b2, a2})) {
        int L=0, U=S-1, mid, r=S;
        while (L<=U) {
            mid=(L+U)>>1;
            if (!dfs(a2, b2, mid+S, b1-1) ||
                !dfs(a2-mid, b2, mid, b1))
                r=mid, U=mid-1;
            else L=mid+1;
        }
        dp[{b1, b2, a2}]=r;
    }
    return z^dp[{b1, b2, a2}]<=a1;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> S >> Q;

    int a, b, c, d;
    while (Q--) {
        cin >> a >> b >> c >> d;
        if (dfs(a-d*S, d, c-b*S, b))
            cout << "YES\n";
        else cout << "NO\n";
    }
}
