#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

int mod_pow(int n, int k, int mod) {
    int r=1;
    while (k) {
        if (k&1) r=1LL*r*n%mod;
        n=1LL*n*n%mod;
        k>>=1;
    }
    return r;
}

int mod_inv(int a, int mod) {
    int b=mod, u=1, v=0;
    while (b) {
        int t=a/b;
        a-=t*b, swap(a, b);
        u-=t*v, swap(u, v);
    }
    u%=mod;
    if (u<0) u+=mod;
    return u;
}

vector<int> solve_sys(
    const vector<vector<int>> &A,
    const vector<int> &b,
    int p
) {
    int n=A.size();
    vector M=A;
    vector rhs=b;
    vector<int> idx(n, -1);
    int r=0;

    for (int c=0; c<n && r<n; c++) {
        int s=-1;
        for (int i=r; i<n; i++) if (M[i][c]%p) {
            s=i;
            break;
        }
        if (s==-1) continue;
        swap(M[r], M[s]);
        swap(rhs[r], rhs[s]);

        int inv=mod_inv(M[r][c], p);
        for (int j=c; j<n; j++) M[r][j]=1LL*M[r][j]*inv%p;
        rhs[r]=1LL*rhs[r]*inv%p;
        for (int i=0; i<n; i++) if (i!=r && M[i][c]) {
            int f=M[i][c];
            for (int j=c; j<n; j++) {
                M[i][j]-=1LL*f*M[r][j]%p;
                if (M[i][j]<0) M[i][j]+=p;
            }
            rhs[i]-=1LL*f*rhs[r]%p;
            if (rhs[i]<0) rhs[i]+=p;
        }
        idx[c]=r++;
    }

    for (int i=r; i<n; i++) if (rhs[i]%p)
        return {};
    vector<int> x(n);
    for (int i=0; i<n; i++) if (idx[i]!=-1)
        x[i]=rhs[idx[i]]%p;
    return x;
}

vector<int> kernel_vec(const vector<vector<int>> &A, int p) {
    int n=A.size();
    vector M=A;
    vector<int> idx(n, -1);
    int r=0;

    for (int c=0; c<n && r<n; c++) {
        int sel=-1;
        for (int i=r; i<n; i++) if (M[i][c]%p) {
            sel=i;
            break;
        }
        if (sel==-1) continue;
        swap(M[r], M[sel]);

        int inv=mod_inv(M[r][c], p);
        for (int j=c; j<n; j++) M[r][j]=1LL*M[r][j]*inv%p;
        for (int i=0; i<n; i++) if (i!=r && M[i][c]) {
            int f=M[i][c];
            for (int j=c; j<n; j++) {
                M[i][j]-=1LL*f*M[r][j]%p;
                if (M[i][j]<0) M[i][j]+=p;
            }
        }
        idx[c]=r++;
    }

    int col=-1;
    for (int c=0; c<n; c++) if (idx[c]==-1) {
        col=c;
        break;
    }
    vector<int> x(n);
    x[col]=1;
    for (int c=n-1; c>=0; c--) if (idx[c]!=-1) {
        int row=idx[c], s=0;
        for (int j=c+1; j<n; j++)
            s=(s+1LL*M[row][j]*x[j]%p)%p;
        x[c]=(p-s)%p;
    }
    return x;
}

vector<vector<int>> matrix(int n, int mod) {
    vector A(n, vector<int>(n));
    for (int i=0; i<n; i++) {
        int pw=1;
        for (int j=0; j<n; j++) {
            int v=pw;
            if (i==j && --v<0) v+=mod;
            A[i][j]=v;
            pw=1LL*pw*i%mod;
        }
    }
    return A;
}

vector<int> lift_prime(int n, int p, int e) {
    auto A=matrix(n, p);
    vector<int> x=kernel_vec(A, p);

    int mod=1;
    for (int t=1; t<e; t++) {
        mod*=p;
        int mod2=mod*p;
        auto B=matrix(n, mod2);

        vector<int> rhs(n);
        for (int i=0; i<n; i++) {
            int s=0;
            for (int j=0; j<n; j++)
                s=(s+1LL*B[i][j]*x[j]%mod2)%mod2;
            rhs[i]=(p-s/mod%p)%p;
        }
        vector<int> d=solve_sys(A, rhs, p);
        for (int i=0; i<n; i++)
            (x[i]+=mod*d[i])%=mod2;
    }

    int pe=1;
    for (int i=0; i<e; i++) pe*=p;
    for (int &v: x) v%=pe;
    return x;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int, int>> fac;
    int x=n;
    for (int p=2; p*p<=x; p++) if (x%p==0) {
        int e=0;
        while (x%p==0) x/=p, e++;
        fac.emplace_back(p, e);
    }
    if (x>1) fac.emplace_back(x, 1);

    if (n==1) return !(cout << 0 << '\n');
    vector<int> gen(n, 0);
    for (auto [p, e]: fac) {
        int pe=1;
        for (int i=0; i<e; i++) pe*=p;
        vector<int> part=lift_prime(n, p, e);
        int M=n/pe;
        int t=mod_inv(M%pe, pe);
        int coef=1LL*M*t%n;

        for (int i=0; i<n; i++)
            (gen[i]+=1LL*coef*part[i]%n)%=n;
    }

    vector<vector<int>> r(n);
    for (int k=0; k<n; k++) {
        vector<int> cur(n);
        for (int i=0; i<n; i++)
            cur[i]=1LL*k*gen[i]%n;
        r[k]=move(cur);
    }

    ranges::sort(r, [&](const vector<int> &a, const vector<int> &b) {
        for (int i=n-1; i>=0; i--)
            if (a[i]!=b[i]) return a[i]<b[i];
        return false;
    });
    for (const auto &v: r) {
        for (int i=n-1; i>=0; i--)
            cout << v[i] << ' ';
        cout << '\n';
    }
}