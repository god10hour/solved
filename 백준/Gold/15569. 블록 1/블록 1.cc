#include <bits/stdc++.h>
using namespace std;
const int MOD=1999;

struct Matrix {
    vector<vector<int>> v;
    Matrix(int n, bool x=0): v(n, vector<int>(n)) {
        if (x)
            for (int i=0; i<n; i++)
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
    friend Matrix pow(Matrix x, int64_t k) {
        int n=x.v.size();
        Matrix r(n, 1);
        while (k) {
            if (k&1)
                r=r*x;
            x=x*x;
            k>>=1;
        }
        return r;
    }
};

int pow(int n, int k, const int mod) {
    int r=1;
    while (k) {
        if (k&1)
            r=r*n%mod;
        n=n*n%mod;
        k>>=1;
    }
    return r;
}

vector<int> multiply(const Matrix &m, const vector<int> &v) {
    int n=v.size();
    vector<int> r(n);
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            r[i]+=v[j]*m.v[i][j], r[i]%=MOD;
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int64_t n, m;
    cin >> n >> m;
    if (n==1) return !(cout << 1);
    if (n==m) return !(cout << pow(2, n, MOD)-1);
    if (n>=m) return !(cout << pow(2, m-1, MOD));

    Matrix A(n);
    for (int i=0; i<n-1; i++)
        A[0][i]=A[i+1][i]=1;
    A[0][n-1]=pow(2, n-1, MOD);
    vector<int> r(n);
    r[n-1]=1;
    for (int i=n-2; i>0; i--)
        r[i]=r[i+1]*2%MOD;
    r[0]=(A[0][n-1]*2-1)%MOD;
    A=pow(A, m-n);
    r=multiply(A, r);
    cout << r[0];
}