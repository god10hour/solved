#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

template <typename Type>
struct Poi {
    Type x, y;
    Poi()=default;
    explicit Poi(Type x, Type y): x(x), y(y) {}

    Poi operator+(const Poi &p) const { return Poi(x+p.x, y+p.y); }
    Poi operator-(const Poi &p) const { return Poi(x-p.x, y-p.y); }
    Poi operator*(Type k)       const { return Poi(x*k, y*k); }
    friend Poi operator*(Type k, const Poi &p) { return Poi(p.x*k, p.y*k); }

    Type operator*(const Poi &p) const { return x*p.x + y*p.y; }
    Type operator/(const Poi &p) const { return x*p.y - y*p.x; }

    bool operator==(const Poi &p) const { return x==p.x && y==p.y; }
    bool operator< (const Poi &p) const { return x<p.x || (x==p.x && y<p.y); }
    bool operator> (const Poi &p) const { return x>p.x || (x==p.x && y>p.y); }

    static Type dis(const Poi &a, const Poi &b) {
        Type dx=a.x-b.x, dy=a.y-b.y;
        return dx*dx + dy*dy;
    }
    static int ccw(const Poi &a, const Poi &b, const Poi &c) {
        Type d=a.x*b.y + b.x*c.y + c.x*a.y - a.x*c.y - b.x*a.y - c.x*b.y;
        return (d>0)-(d<0);
    }
};
using P=Poi<lint>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    lint n, X=0, Y=0;
    cin >> n;
    vector<Poi<lint>> P(n);
    for (int i=0; i<n; i++) {
        cin >> P[i].x >> P[i].y;
        X+=P[i].x, Y+=P[i].y;
    }
    ranges::sort(
        P, [&](auto a, auto b) {
            Poi<lint> o(0, 0);
            if (a>o^b>o)
                return a>b;
            if (P::ccw(o, a, b))
                return P::ccw(o, a, b)>0;
            return a*a < b*b;
        }
    );
    lint xs=0, ys=0, r=0, j=0;
    for (int i=0; i<n; xs-=P[i].x, ys-=P[i].y, i++) {
        while (j<i+n && (P[i]/P[j%n]>0 || (P[i]/P[j%n]==0 && P[i]*P[j%n]>0)))
            xs+=P[j%n].x, ys+=P[j%n].y, j++;
        Poi a(xs, ys), b(X, Y);
        r=max({r, a*a, P::dis(a, b)});
    }
    cout << r << '\n';
}