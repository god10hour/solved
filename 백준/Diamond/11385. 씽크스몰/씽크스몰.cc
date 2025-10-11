#include <bits/stdc++.h>
#define int int64_t
using namespace std;
const double PI=acos(-1);
typedef complex<long double> cpx;

void FFT(vector<cpx> &v, bool inv) {
    int s=v.size();
    for (int i=1, j=0; i<s; i++) {
        int b=s/2;
        while (j>=b)
            j-=b, b/=2;
        j+=b;
        if (i<j) swap(v[i], v[j]);
    }
    for (int k=1; k<s; k*=2) {
        long double ang=inv?PI/k:-PI/k;
        cpx w(cos(ang), sin(ang));
        for (int i=0; i<s; i+=k*2) {
            cpx uni(1, 0);
            for (int j=0; j<k; j++) {
                cpx a=v[i+j], b=v[i+j+k]*uni;
                v[i+j]=a+b;
                v[i+j+k]=a-b;
                uni*=w;
            }
        }
    }
    if (inv) for (int i=0; i<s; i++) v[i]/=s;
}

vector<int> CVL(vector<int>& V, vector<int>& U) {
    vector<cpx> v(V.begin(), V.end()), u(U.begin(), U.end());
    int s=2;
    while (s<v.size()+u.size()) s*=2;
    v.resize(s), FFT(v, 0);
    u.resize(s), FFT(u, 0);
    vector<cpx> w(s);
    vector<int> r(s);
    for (int i=0; i<s; i++)
        w[i]=v[i]*u[i];
    FFT(w, 1);
    for (int i=0; i<s; i++)
        r[i]=round(w[i].real());
    return r;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, r=0;
    cin >> n >> m;
    vector<int> v(n+1), u(m+1), V, U, w11, w12, w21, w22;
    for (auto& i:v) cin >> i;
    for (auto& i:u) cin >> i;

    V=v, U=u;
    for (auto& i:V) i&=(1<<10)-1;
    for (auto& i:U) i&=(1<<10)-1;
    w22=CVL(V, U);
    V=v, U=u;
    for (auto& i:V) i>>=10;
    for (auto& i:U) i&=(1<<10)-1;
    w12=CVL(V, U);
    V=v, U=u;
    for (auto& i:V) i&=(1<<10)-1;
    for (auto& i:U) i>>=10;
    w21=CVL(V, U);
    V=v, U=u;
    for (auto& i:V) i>>=10;
    for (auto& i:U) i>>=10;
    w11=CVL(V, U);

    for (int i=0; i<=n+m; i++)
        r^=(w11[i]<<20)+((w12[i]+w21[i])<<10)+w22[i];
    cout << r;
}