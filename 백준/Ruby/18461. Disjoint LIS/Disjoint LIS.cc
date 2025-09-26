#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const int MOD=998244353;

int power(int n, int k) {
    int r=1;
    while (k) {
        if (k&1)
            r=r*n%MOD;
        n=n*n%MOD;
        k/=2;
    }
    return r;
}

int hook(const vector<int> &shape) {
    if (shape.empty()) return 1;
    int rs=shape.size();
    int c=0;
    for (int x: shape)
        c=max(c, x);

    vector<int> hei(c+1, 0);
    for (int j=1; j<=c; j++) {
        int s=0;
        for (int i=0; i<rs; i++)
            if (shape[i]>=j) s++;
        hei[j]=s;
    }

    int prd=1;
    for (int i=0; i<rs; ++i)
        for (int j=1; j<=shape[i]; j++) {
            int h=shape[i]-j+hei[j]-(i+1)+1;
            prd=prd*h%MOD;
        }
    return prd;
}

void part(
    int r, int max, int pre,
    vector<int> &cur, vector<vector<int>> &out
) {
    if (r==0) {
        out.push_back(cur);
        return;
    }
    int up=min({r, max, pre});
    for (int p=up; p>0; p--) {
        cur.push_back(p);
        part(r-p, max, p, cur, out);
        cur.pop_back();
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> fac(n+1, 1), ifac(n+1, 1);
    for (int i=1; i<n+1; i++)
        fac[i]=i*fac[i-1]%MOD;
    ifac[n]=power(fac[n], MOD-2);
    for (int i=n; i>0; i--)
        ifac[i-1]=i*ifac[i]%MOD;

    int r=0;
    for (int k=1; k*2<n+1; k++) {
        int m=n-k*2;
        vector<vector<int>> tail;
        vector<int> cur;
        part(m, k, k, cur, tail);
        if (m==0 && tail.empty())
            tail.push_back(vector<int>{});
        for (const auto &mu: tail) {
            vector<int> shape;
            shape.push_back(k);
            shape.push_back(k);
            for (int x: mu)
                shape.push_back(x);
            int prd=hook(shape);
            int f=fac[n]*power(prd, MOD-2)%MOD;
            r+=f*f%MOD;
            if (r>=MOD) r-=MOD;
        }
    }
    cout << r;
}
