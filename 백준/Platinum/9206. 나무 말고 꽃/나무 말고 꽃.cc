#include <bits/stdc++.h>
using namespace std;
constexpr double EPS=1e-6;

double func(double a, double b, double x) {
    double r=a*exp(-x*x)+b*sqrt(x);
    return r*r;
}

double inte(double a, double b, double h) {
    int k=1;
    double V=h*(func(a, b, 0)+func(a, b, h))/2.0, Vpre;
    do {
        double t=0;
        k*=2;
        for (int i=1; i<k; i+=2) t+=func(a, b, h*i/k);
        Vpre=V;
        V=V/2.0+t*h/k;
    } while (fabs(V-Vpre)>EPS);
    return V;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    double V, emin=1e15;
    int n, idx;
    cin >> V >> n;
    V/=acos(-1.0);

    for (int i=0; i<n; i++) {
        double a, b, h;
        cin >> a >> b >> h;
        double e=fabs(V-inte(a, b, h));
        if (e<emin) emin=e, idx=i;
    }
    cout << idx << '\n';
}