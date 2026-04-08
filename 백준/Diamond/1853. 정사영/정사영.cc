#include <bits/stdc++.h>
using namespace std;
constexpr double eps=1e-12L;
using Poi=array<double, 2>;

double width_at(const vector<Poi> &p, double z) {
    double mn=1e64, mx=-1e64;
    int n=p.size();

    for (int i=0; i<n; i++) {
        auto &[u1, z1]=p[i];
        auto &[u2, z2]=p[(i+1)%n];

        if (fabs(z1-z2)<eps) {
            if (fabs(z-z1)<eps) {
                mn=min(mn, min(u1, u2));
                mx=max(mx, max(u1, u2));
            }
            continue;
        }

        double lo=min(z1, z2), hi=max(z1, z2);
        if (z+eps<lo || hi+eps<z) continue;
        double u=u1+(z-z1)/(z2-z1)*(u2-u1);
        mn=min(mn, u);
        mx=max(mx, u);
    }
    if (mx<mn) return 0.0;
    return mx-mn;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int nx, ny;
    cin >> nx;
    vector<Poi> pxz(nx);
    for (auto &[u, z]: pxz) cin >> u >> z;
    cin >> ny;
    vector<Poi> pyz(ny);
    for (auto &[u, z]: pyz) cin >> u >> z;

    vector<double> zs;
    zs.reserve(nx+ny);
    for (auto &[u, z]: pxz) zs.emplace_back(z);
    for (auto &[u, z]: pyz) zs.emplace_back(z);

    ranges::sort(zs);
    zs.erase(ranges::unique(zs, [](double a, double b) {
        return fabs(a-b)<eps;
    }).begin(), zs.end());

    double r=0.0;

    for (int i=0; i+1<zs.size(); i++) {
        double z0=zs[i], z1=zs[i+1];
        double mid=(z0+z1)*0.5;
        if (fabs(z1-z0)<1e-12) continue;

        double wx0=width_at(pxz, z0);
        double wxm=width_at(pxz, mid);
        double wx1=width_at(pxz, z1);

        double wy0=width_at(pyz, z0);
        double wym=width_at(pyz, mid);
        double wy1=width_at(pyz, z1);

        double f0=wx0*wy0;
        double fm=wxm*wym;
        double f1=wx1*wy1;

        r+=(z1-z0)*(f0+4.0*fm+f1)/6.0;
    }
    cout << fixed << setprecision(6) << r << '\n';
}