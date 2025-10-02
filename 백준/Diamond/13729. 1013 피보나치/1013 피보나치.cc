#include <bits/stdc++.h>
#define int uint64_t
using namespace std;

int mod;
struct Matrix {
    vector<vector<int>> v;
    Matrix(int n, bool x=0): v(n, vector<int>(n)) {
        if (x) for (int i=0; i<n; i++)
            v[i][i]=1;
    }
    vector<int> &operator[](int i) {
        return v[i];
    }
    friend Matrix operator*(Matrix a, Matrix b) {
        int n=a.v.size();
        Matrix r(n);
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                for (int k=0; k<n; k++)
                    r[i][j]=(r[i][j]+(__uint128_t)a[i][k]*b[k][j])%mod;
        return r;
    }
    friend Matrix Pow(Matrix x, int k) {
        int n=x.v.size();
        Matrix r(n, 1);
        while (k) {
            if (k&1) r=r*x;
            x=x*x;
            k>>=1;
        }
        return r;
    }
};

int fibo(int n) {
    Matrix T(2);
    T.v={{1, 1}, {1, 0}};
    T=Pow(T, n);
    return T[0][1];
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    if (n==1e13) return !(cout << -1);

    mod=1e3;
    int pis=1500, N=n%mod;
    vector<int> cand;
    for (int i=0; i<pis; i++)
        if (fibo(i)==N)
            cand.push_back(i);
    if (cand.empty()) return !(cout << -1);

    for (int k=4; k<14; k++) {
        mod*=10, pis*=10;
        N=n%mod;
        vector<int> nxt;
        int pre=pis/10ULL;

        for (int base: cand) {
            for (int i=0; i<10; i++) {
                int idx=base+i*pre;
                if (fibo(idx)==N)
                    nxt.push_back(idx);
            }
        }
        sort(nxt.begin(), nxt.end());
        cand.swap(nxt);
        if (cand.empty()) return !(cout << -1);
    }
    cout << cand.front();
}