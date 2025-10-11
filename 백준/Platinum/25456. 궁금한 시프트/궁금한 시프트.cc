#include <bits/stdc++.h>
#define int int64_t
using namespace std;
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

vector<int> conv(vector<int> &V, vector<int> &U) {
    vector<cpx> v(V.begin(), V.end());
    vector<cpx> u(U.begin(), U.end());
    int s=1;
    while (s<v.size()+u.size())
        s*=2;
    v.resize(s), FFT(v, 0);
    u.resize(s), FFT(u, 0);
    vector<int> w(s);
    for (int i=0; i<s; i++)
        v[i]*=u[i];
    FFT(v, 1);
    for (int i=0; i<s; i++)
        w[i]=round(v[i].real());
    return w;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, r=0;
    string s, t;
    cin >> s >> t;
    n=s.length();
    vector<int> v(n), u(n);
    for (int i=0; i<n; i++)
        v[i]=s[i]-'0', u[i]=t[i]-'0';
    auto w=conv(v, u);
    for (int i: w) r=max(r, i);
    cout << r << '\n';
}