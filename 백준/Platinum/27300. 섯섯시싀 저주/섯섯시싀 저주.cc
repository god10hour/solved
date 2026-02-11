#include <bits/stdc++.h>
using namespace std;
using rea=long double;
using lint=int64_t;
constexpr rea PI=acosl(-1.0L);
constexpr rea EPS=1e-12L;

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

    bool operator==(const Poi &p) const { return fabsl(x-p.x)<=EPS && fabsl(y-p.y)<=EPS; }
    bool operator< (const Poi &p) const { return x<p.x || (x==p.x && y<p.y); }
    bool operator> (const Poi &p) const { return x>p.x || (x==p.x && y>p.y); }

    Poi rot90() const { return Poi(-y, x); }
    static Type dis(const Poi &a, const Poi &b) {
        Type dx=a.x-b.x, dy=a.y-b.y;
        return dx*dx + dy*dy;
    }
    static int ccw(const Poi &a, const Poi &b, const Poi &c) {
        Type d=a.x*b.y + b.x*c.y + c.x*a.y - a.x*c.y - b.x*a.y - c.x*b.y;
        return (d>0)-(d<0);
    }

    static int half(const Poi &p) { return p.y<-EPS || (fabsl(p.y)<=EPS && p.x<-EPS); }
    static void sort_angle(vector<Poi> &v, const Poi &p) {
        ranges::sort(v, [&](const Poi &A, const Poi &B) {
            Poi a=A-p;
            Poi b=B-p;
            int ha=half(a), hb=half(b);
            if (ha!=hb) return ha<hb;
            Type cr=a/b;
            if (fabsl(cr)>EPS) return cr>0;
            return a*a<b*b;
        });
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(12);
    lint n, r;
    cin >> n >> r;
    Poi<rea> s(0, 0);
    for (int i=0; i<n; i++) {
        int x, y;
        cin >> x >> y;
        auto sqrt_int=[&](lint v) {
            return ((v>0)-(v<0))*sqrtl(llabs(v));
        };
        s=s+Poi(sqrt_int(x), sqrt_int(y));
    }
    cout << 4.L/3.L*r+8.L/3.L*(s*s-n*r)/(n*(n-1)) << '\n';
}