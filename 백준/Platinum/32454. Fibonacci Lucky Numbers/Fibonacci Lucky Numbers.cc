#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const int MOD=1e10;
const int PIS[]={
    1'600'000'000LL,
    4'000'000'000LL,
    15'000'000'000LL
};

struct Matrix {
    vector<vector<int>> v;
    Matrix(int n, bool x=0): v(n, vector<int>(n)) {
        if (x) for (int i=0; i<n; i++)
            v[i][i]=1;
    }
    vector<int> &operator[](int i) {
        return v[i];
    }
    friend Matrix operator*(Matrix &a, Matrix &b) {
        int n=a.v.size();
        Matrix r(n);
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                for (int k=0; k<n; k++)
                    r[i][j]=(r[i][j]+(__int128)a[i][k]*b[k][j])%MOD;
        return r;
    }
    Matrix pow(int k) const {
        Matrix x=*this, r(v.size(), 1);
        while (k) {
            if (k&1)
                r=r*x;
            x=x*x;
            k/=2;
        }
        return r;
    }
};

int pow(int n, int k, int mod) {
    int r=1;
    while (k) {
        if (k&1)
            r=(__int128)r*n%mod;
        n=(__int128)n*n%mod;
        k/=2;
    }
    return r;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i=0; i<3; i++)
            n=pow(7, n, PIS[i]);
        Matrix T(2);
        T.v={{1, 1}, {1, 0}};
        T=T.pow(n-1);
        cout << setw(10) << setfill('0');
        cout << T[0][0] << '\n';
    }
}