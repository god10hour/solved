#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
using Matrix=vector<vector<lint>>;

static Matrix operator*(const Matrix &a, const Matrix &b) {
    int n=a.size();
    Matrix r(n, vector<lint>(n));
    for (int i=0; i<n; i++)
        for (int k=0; k<n; k++) if (a[i][k])
            for (int j=0; j<n; j++) if (b[k][j])
                r[i][j]+=a[i][k]*b[k][j];
    return r;
}

static lint trace(const Matrix &a) {
    int n=a.size();
    lint r=0;
    for (int i=0; i<n; i++) r+=a[i][i];
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int a, b, m, n;
    while (1) {
        cin >> a >> m >> b >> n;
        if (a==0 && b==0 && m==0 && n==0) return 0;
        int d=m*n;
        Matrix A(d, vector<lint>(d));

        auto idx=[&](int i, int j) { return i*n+j; };
        for (int i=0; i<m; i++) for (int j=0; j<n; j++) {
            lint from=idx(i, j);
            if (i+1<m)
                A[idx(i+1, j)][from]++;
            else A[idx(0, j)][from]+=a;
            if (j+1<n)
                A[idx(i, j+1)][from]++;
            else A[idx(i, 0)][from]+=b;
        }

        vector<lint> s(d+1), r(d+1);
        Matrix cur=A;
        r[0]=1;
        for (int i=1; i<=d; i++) {
            s[i]=trace(cur);
            cur=cur*A;
        }
        for (int i=1; i<=d; i++) {
            lint v=s[i];
            for (int k=1; k<i; k++) v+=r[k]*s[i-k];
            r[i]=-v/i;
        }
        for (int i=0; i<=d; i++) cout << r[i] << ' ';
        cout << '\n';
    }
}