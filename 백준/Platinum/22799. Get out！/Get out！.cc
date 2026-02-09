#include <bits/stdc++.h>
using namespace std;
using rea=long double;
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

struct Circle {
    Poi<rea> c;
    rea r, p;
};
rea norm(rea a) {
    while (a<0) a+=PI*2;
    while (a>=PI*2) a-=PI*2;
    return a;
}

static rea loss_at(const vector<Circle> &cs, const Poi<rea> &s, rea ang) {
    Poi u(cosl(ang), sinl(ang));
    rea loss=0;
    for (const auto &o:cs) {
        Poi<rea> v=o.c-s;
        rea d=sqrtl(v*v), proj=v*u, D;
        if (proj<=0) D=d;
        else {
            rea cr=fabsl(v/u);
            D=cr;
        }
        if (D<o.r-EPS) return 1e100L;
        if (D<=2*o.r+EPS) {
            rea t=(2*o.r-D)/o.r;
            if (t<0) t=0;
            loss+=o.p*t;
        }
    }
    return loss;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(3);

    int n;
    while (cin >> n, n!=0) {
        vector<Circle> cs(n);
        for (int i=0; i<n; i++) {
            rea x, y, r, p;
            cin >> x >> y >> r >> p;
            cs[i]={Poi(x, y), r, p};
        }
        rea sx, sy, E;
        cin >> sx >> sy >> E;
        Poi s(sx, sy);
        vector<pair<rea, rea>> seg;
        seg.reserve(n*2);

        bool no=false;
        for (const auto &o:cs) {
            Poi<rea> v=o.c-s;
            rea d=sqrtl(v*v);
            if (d<o.r-EPS) { no=true; break; }
            if (d<=o.r+EPS) continue;

            rea th=atan2l(v.y, v.x);
            rea a=asinl(min(1.0L, o.r/d));
            rea L=norm(th-a), R=norm(th+a);

            if (L<=R) seg.emplace_back(L, R);
            else {
                seg.emplace_back(L, PI*2);
                seg.emplace_back(0, R);
            }
        }
        if (no) {
            cout << "No way to escape\n";
            continue;
        }

        vector<pair<rea, rea>> bad;
        if (!seg.empty()) {
            ranges::sort(seg);
            auto cl=seg[0].first, cr=seg[0].second;
            for (int i=1; i<seg.size(); i++)
                if (seg[i].first<=cr+1e-18L)
                    cr=max(cr, seg[i].second);
                else {
                    bad.emplace_back(cl, cr);
                    cl=seg[i].first, cr=seg[i].second;
                }
            bad.emplace_back(cl, cr);
        }
        vector<pair<rea, rea>> use;
        if (bad.empty())
            use.emplace_back(0, PI*2);
        else {
            if (bad[0].first>0) use.emplace_back(0, bad[0].first);
            for (int i=0; i+1<bad.size(); i++)
                if (bad[i].second<bad[i+1].first)
                    use.emplace_back(bad[i].second, bad[i+1].first);
            if (bad.back().second<2*PI) use.emplace_back(bad.back().second, PI*2);
        }

        rea rs=1e100L;
        for (auto [L, R]: use) {
            if (R-L<=1e-18L) continue;
            rea ra=L, rv=1e100L;

            for (int i=0; i<=240; i++) {
                rea a=L+(R-L)*i/240;
                rea v=loss_at(cs, s, a);
                if (v<rv) rv=v, ra=a;
            }

            rea a0=max(L, ra-(R-L)/480);
            rea a1=min(R, ra+(R-L)/480);
            for (int i=0; i<120; i++) {
                rea m1=a0+(a1-a0)/3, m2=a1-(a1-a0)/3;
                if (loss_at(cs, s, m1)<loss_at(cs, s, m2))
                    a1=m2;
                else a0=m1;
            }
            rea cand=loss_at(cs, s, (a0+a1)/2);
            cand=min(cand, loss_at(cs, s, L));
            cand=min(cand, loss_at(cs, s, R));
            rs=min(rs, cand);
        }

        if (rs>9e99L || rs>E+1e-9L)
            cout << "No way to escape\n";
        else {
            rea rem=E-rs;
            if (rem<0) rem=0;
            cout << rem << '\n';
        }
    }
}