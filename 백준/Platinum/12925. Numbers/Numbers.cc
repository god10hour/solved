#include <bits/stdc++.h>
#define MOD 1000
using namespace std;

struct Matrix {
    vector<vector<int>> v;
    Matrix(int n, bool x=0):v(n, vector<int>(n)) {
        if (x)
            for (int i=0; i<n; i++)
                v[i][i]=1;
    }
    vector<int>& operator[](int i) {
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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    for (int i=0; i<t; i++) {
        cout << "Case #" << i+1 << ": ";
        int n;
        cin >> n;
        Matrix T(2);
        T[0][0]=6, T[0][1]=-4;
        T[1][0]=1, T[1][1]=0;
        T=Pow(T, n-1);
        int r=(T[0][0]*6+T[0][1]*2)%MOD;
        r=(r-1+MOD)%MOD;
        cout << setfill('0') << setw(3) << r << '\n';
    }
}