#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const int MOD=1e9+7;
const int INV=(MOD+1)/2;

int k;
static vector<int> phi, Phi;
static unordered_map<int, int> dpf, dpp;

struct Matrix {
    vector<vector<int>> v;
    Matrix(int n, bool x=0): v(n, vector<int>(n)) {
        if (x) for (int i=0; i<n; i++) v[i][i]=1;
    }
    vector<int> &operator[](int i) { return v[i]; }
    friend Matrix operator*(const Matrix& a, const Matrix& b) {
        int n=a.v.size();
        Matrix r(n);\
        for (int i=0; i<n; i++)
            for (int k=0; k<n; k++) if (a.v[i][k])
                for (int j=0; j<n; j++)
                    r.v[i][j]=(r.v[i][j]+a.v[i][k]*b.v[k][j])%MOD;
        return r;
    }
    friend Matrix Pow(Matrix x, int64_t k) {
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
    if (n==0) return 0;
    if (auto it=dpf.find(n); it!=dpf.end()) return it->second;
    Matrix A(2);
    A.v={{1, 1}, {1, 0}};
    A=Pow(A, n);
    int a=A[1][1], b=A[0][1], c=A[0][0];
    dpf[n-1]=a;
    dpf[n+1]=c;
    return dpf[n]=b;
}

int sum(int l, int r) {
    if (l>r) return 0;
    int s=(fibo(r+2)-fibo(l+1))%MOD;
    if (s<0) s+=MOD;
    return s;
}

int phin(int n) {
    if (n<=k) return Phi[n];
    if (auto it=dpp.find(n); it!=dpp.end()) return it->second;
    int N=n%MOD;
    int s=N*(N+1)%MOD;
    s=s*INV%MOD;
    for (int l=2, r; l<=n; l=r+1) {
        int v=n/l;
        r=n/v;
        int sub=phin(v);
        s-=(r-l+1)*sub%MOD;
        if (s<0) s+=MOD;
    }
    return dpp[n]=s;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    k=max<int>(1, (int)floor(powl(n, 2.0L/3.0L)));
    phi.assign(k+1, 0);
    Phi.assign(k+1, 0);
    iota(phi.begin(), phi.end(), 0);
    for (int i=2; i<k+1; i++)
        if (i==phi[i])
            for (int j=i; j<k+1; j+=i)
                phi[j]=phi[j]/i*(i-1);
    for (int i=1; i<=k; i++)
        Phi[i]=(phi[i]+Phi[i-1])%MOD;

    int s=0;
    for (int l=1, r; l<=n; l=r+1) {
        int v=n/l;
        r=n/v;
        int coef=(2LL*phin(v)-1)%MOD;
        if (coef<0) coef+=MOD;
        int seg=sum(l, r);
        s+=seg*coef, s%=MOD;
        if (s<0) s+=MOD;
    }
    cout << s;
}