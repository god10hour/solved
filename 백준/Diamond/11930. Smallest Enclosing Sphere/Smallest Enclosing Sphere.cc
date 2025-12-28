#include <bits/stdc++.h>
using namespace std;
using ldb=long double;

template<typename Type>
struct Vec {
    Type x, y, z;
    Vec()=default;
    explicit Vec(Type x, Type y, Type z): x(x), y(y), z(z) {}

    Vec operator+(const Vec &o) const { return Vec(x+o.x, y+o.y, z+o.z); }
    Vec operator-(const Vec &o) const { return Vec(x-o.x, y-o.y, z-o.z); }
    Vec operator*(Type k) const { return Vec(x*k, y*k, z*k); }
    Vec& operator+=(const Vec& o) { x+=o.x; y+=o.y; z+=o.z; return *this; }

    friend Type operator*(const Vec &a, const Vec &b) {
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }
    friend  Vec operator/(const Vec &a, const Vec &b) {
        return Vec(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
    }

    static Type norm2(const Vec &a) { return a*a; }
    static Type norm(const Vec &a) { return sqrtl(norm2(a)); }

    static Vec normalize(const Vec &a) {
        Type n=norm(a);
        return n==0? a: a*(1.0L/n);
    }
};
using Poi=Vec<double>;

double enclose(const vector<Poi> &pts) {
    int n=pts.size();
    Poi p(0, 0, 0);
    for (int i=0; i<n; i++) p+=pts[i];
    p=p*(1.0L/n);

    double rat=0.1, v=0;
    for (int i=0; i<10000; i++) {
        v=-1;
        int idx=-1;
        for (int j=0; j<n; j++) {
            double k=Poi::norm2(pts[j]-p);
            if (v<k) v=k, idx=j;
        }
        p+=(pts[idx]-p)*rat;
        rat*=0.998;
    }
    return sqrt(v);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(2);
    int n;
    cin >> n;
    vector<Poi> pts(n);
    for (int i=0; i<n; i++)
        cin >> pts[i].x >> pts[i].y >> pts[i].z;
    cout << enclose(pts) << '\n';
}