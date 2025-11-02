#include <bits/stdc++.h>
using namespace std;
#define int long long
const double PI=acos(-1);
typedef complex<double> cpx;

void FFT(vector<cpx> &v, bool inv) {
    int s=v.size();
    for (int i=1, j=0; i<s; i++) {
        int b=s/2;
        while (j>=b)
            j-=b, b/=2;
        j+=b;

        if (i<j)
            swap(v[i], v[j]);
    }

    for (int k=1; k<s; k*=2) {
        double ang=inv?PI/k:-PI/k;
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

    if (inv)
        for (int i=0; i<s; i++)
            v[i]/=s;
}

vector<cpx> mul(vector<cpx> &v, vector<cpx> &u) {
    int s=2;
    while (s<v.size()+u.size())
        s*=2;
    v.resize(s), FFT(v, 0);
    u.resize(s), FFT(u, 0);

    vector<cpx> w(s);
    for (int i=0; i<s; i++)
        w[i]=v[i]*u[i];
    FFT(w, 1);
    return w;
}

main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin >> n;
    vector<cpx> v(n*2), u(n);

    for (int i=0; i<n; i++)
        cin >> k, v[i]=v[i+n]=cpx(k, 0);
    for (int i=0; i<n; i++)
        cin >> k, u[n-i-1]=cpx(k, 0);
    vector<cpx> w=mul(v, u);
    int s=0;
    for (int i=0; i<w.size(); i++)
        s=max(s, (int)round(w[i].real()));

    cout << s;
}