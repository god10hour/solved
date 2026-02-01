#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
using Lint=__int128_t;

class Melonaid {
public:
    lint n, k;
    Lint k2, S0;
    explicit Melonaid(lint n_, lint k_): n(n_), k(k_) {
        k2=k*k, S0=k*(k+1)/2;
    }

    lint run() {
        lint t=(n-1)/(k2+1);
        Lint m=sum(t);

        if (n==m) return Lint(t+1)*(k+1);
        Lint A=t*(k2+1)+1;
        Lint rin=n-A-(n>m);
        Lint j=t*k2+rin+1;
        return j+(j-1)/k;
    }

private:
    Lint sum(lint i) {
        if (i==0) return S0;
        lint t=i/k, j=i%k;

        Lint m=sum(t), A=t*(k2+1)+1;
        Lint r1=Lint(j)*k, r2=r1+k-1;
        Lint base=k*A+sum_arith(r1, r2);
        Lint p=m-A, c;

        if (p<=r1) c=k;
        else if (p>r2) c=0;
        else c=r2-p+1;
        return base+c;
    }
    static Lint sum_arith(Lint l, Lint r) {
        return (l+r)*(r-l+1)/2;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        lint n, k;
        cin >> n >> k;
        Melonaid A(n, k);
        cout << A.run() << '\n';
    }
}