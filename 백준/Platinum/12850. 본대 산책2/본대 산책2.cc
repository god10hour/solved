#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const int MOD=1e9+7;

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
                    r[i][j]+=a[i][k]*b[k][j], r[i][j]%=MOD;
        return r;
    }
    friend Matrix pow(Matrix x, int k) {
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

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    Matrix A(8);
    A.v={
        {0, 1, 1, 0, 0, 0, 0, 0},
        {1, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 1, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 1, 1, 1},
        {0, 0, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 1, 0, 1},
        {0, 0, 0, 0, 1, 0, 1, 0},
    };
    int n;
    cin >> n;
    auto T=pow(A, n);
    cout << T[7][7];
}