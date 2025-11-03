#include <stdio.h>
#define MOD 1000000007
#define ll long long

void mul(ll a[2][2], ll b[2][2]) {
    ll m[2][2];
    for (int i=0; i<2; i++)
        for (int j=0; j<2; j++) {
            m[i][j]=0;
            for (int k=0; k<2; k++)
                m[i][j]=(m[i][j]+a[i][k]*b[k][j])%MOD;
        }
    for (int i=0; i<2; i++)
        for (int j=0; j<2; j++)
            a[i][j]=m[i][j];
}

void pow(ll m[2][2], ll n) {
    if (n<2)
        return;
    ll r[2][2]={1,1,1,0};
    pow(m, n/2);
    mul(m, m);
    if (n%2) mul(m,r);
}

ll f(ll n) {
    if (n<2)
        return n;
    ll m[2][2]={1,1,1,0};
    pow(m, n-1);
    return m[0][0];
}

int main() {
    ll n;
    scanf("%lld", &n);
    printf("%lld", f(n));
}