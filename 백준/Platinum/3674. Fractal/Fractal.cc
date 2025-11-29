#include <bits/stdc++.h>
using namespace std;
using cpx=complex<double>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(10);
    int t;
    cin >> t;
    while (t--) {
        int n, d;
        double f;
        cin >> n;

        vector<cpx> z(n);
        vector<double> L(n);
        for (int i=0; i<n; i++) {
            int xi, yi;
            cin >> xi >> yi;
            z[i]=cpx(xi, yi);
        }
        cin >> d >> f;
        auto warp=[&](const cpx &p, const cpx &a, const cpx &b) ->cpx {
            return (p-z[0])/(z[n-1]-z[0])*(b-a)+a;
        };
        cpx a=z[0], b=z[n-1];
        double u=f;
        L[0]=0.0;
        for (int i=1; i<n; i++)
            L[i]=L[i-1]+abs(z[i]-z[i-1]);
        for (int i=0; i<d; i++) {
            double tar=u*L[n-1];
            auto it=lower_bound(L.begin()+1, L.end()-1, tar);
            int k=it-L.begin();

            cpx a2=warp(z[k-1], a, b);
            cpx b2=warp(z[k], a, b);
            a=a2, b=b2;

            u=(tar-L[k-1])/(L[k]-L[k-1]);
            if (u<0.0) u=0.0;
            if (u>1.0) u=1.0;
        }
        cpx r=a+u*(b-a);
        cout << '(' << r.real() << ',' << r.imag() << ")\n";
    }
}
