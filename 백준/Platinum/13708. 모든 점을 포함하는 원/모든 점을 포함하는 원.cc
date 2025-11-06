#include <bits/stdc++.h>
using namespace std;

struct Poi {
    double x, y;
    Poi(double x=0, double y=0): x(x), y(y) {}

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

double dot(Poi a, Poi b) {
    return a.x*b.x + a.y*b.y;
}
double cross(Poi a, Poi b) {
    return a.x*b.y - a.y*b.x;
}
double dis(Poi a, Poi b) {
    double dx=a.x-b.x, dy=a.y-b.y;
    return hypot(dx, dy);
}

struct Circle {
    Poi cen;
    double r;
};

Poi center(const Poi &a, const Poi &b) {
    return {(a.x+b.x)/2.0, (a.y+b.y)/2.0};
}
Circle circle(Poi a, Poi b) {
    Poi cen=center(a, b);
    return {cen, dis(a, b)/2};
}

Circle circle(Poi a, Poi b, Poi c) {
    double d=2*(a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y));
    double ux=(dot(a, a)*(b.y-c.y) + dot(b, b)*(c.y-a.y) + dot(c, c)*(a.y-b.y))/d;
    double uy=(dot(a, a)*(c.x-b.x) + dot(b, b)*(a.x-c.x) + dot(c, c)*(b.x-a.x))/d;
    Poi cen(ux, uy);
    return {cen, dis(cen, a)};
}

Circle min_circle(const vector<Poi> &v) {
    Circle C{Poi(0, 0), 0};
    int n=v.size();
    for (int i=0; i<n; i++) if (dis(C.cen, v[i])>C.r) {
        C.cen=v[i], C.r=0;
        for (int j=0; j<i; j++) if (dis(C.cen, v[j])>C.r) {
            C=circle(v[i], v[j]);
            for (int k=0; k<j; k++) if (dis(C.cen, v[k])>C.r)
                C=circle(v[i], v[j], v[k]);
        }
    }
    return C;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(2);
    int n;
    cin >> n;
    vector<Poi> v(n);
    for (int i=0; i<n; i++) cin >> v[i].x >> v[i].y;
    Circle C=min_circle(v);
    cout << C.r*2.0;
}