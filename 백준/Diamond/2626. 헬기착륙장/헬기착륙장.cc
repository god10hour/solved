#include <bits/stdc++.h>
using namespace std;

struct Poi {
    long double x, y;
    Poi(long double x=0, long double y=0): x(x), y(y) {}

    Poi operator+(const Poi &p) const {
        return {x+p.x, y+p.y};
    }
    Poi operator-(const Poi &p) const {
        return {x-p.x, y-p.y};
    }
    bool operator<(const Poi &p) const {
        return x<p.x || (x==p.x && y<p.y);
    }
};

long double dot(Poi a, Poi b) {
    return a.x*b.x + a.y*b.y;
}
long double cross(Poi a, Poi b) {
    return a.x*b.y - a.y*b.x;
}
long double dis(Poi a, Poi b) {
    long double dx=a.x-b.x, dy=a.y-b.y;
    return hypotl(dx, dy);
}

struct Circle {
    Poi cen;
    long double r;
};

Poi center(const Poi &a, const Poi &b) {
    return {(a.x+b.x)/2.0, (a.y+b.y)/2.0};
}
Circle circle(Poi a, Poi b) {
    Poi cen=center(a, b);
    return {cen, dis(a, b)/2};
}

Circle circle(Poi a, Poi b, Poi c) {
    long double d=2*(a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y));
    long double ux=(dot(a, a)*(b.y-c.y) + dot(b, b)*(c.y-a.y) + dot(c, c)*(a.y-b.y))/d;
    long double uy=(dot(a, a)*(c.x-b.x) + dot(b, b)*(a.x-c.x) + dot(c, c)*(b.x-a.x))/d;
    Poi cen(ux, uy);
    return {cen, dis(cen, a)};
}

Circle min_circle(const vector<Poi> &v) {
    Circle C{Poi(0, 0), 0};
    int n=v.size();
    random_device rd;
    mt19937 gen(rd());
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    ranges::shuffle(idx, gen);
    for (int i=0; i<n; i++) if (dis(C.cen, v[idx[i]])>C.r) {
        C.cen=v[idx[i]], C.r=0;
        for (int j=0; j<i; j++) if (dis(C.cen, v[idx[j]])>C.r) {
            C=circle(v[idx[i]], v[idx[j]]);
            for (int k=0; k<j; k++) if (dis(C.cen, v[idx[k]])>C.r)
                C=circle(v[idx[i]], v[idx[j]], v[idx[k]]);
        }
    }
    return C;
}
long double round3(long double x) {
    x*=1000.0;
    x=floor(x+0.5);
    return x;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(3);
    int n;
    cin >> n;
    vector<Poi> v(n);
    for (int i=0; i<n; i++) cin >> v[i].x >> v[i].y;
    Circle C=min_circle(v);
    C={{round3(C.cen.x), round3(C.cen.y)}, round3(C.r)};
    cout << C.cen.x/1000.0 << ' ' << C.cen.y/1000.0 << '\n';
    cout << C.r/1000.0 << '\n';
}