#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
using Lint=__int128_t;
constexpr double eps=1e-12;

template <typename Type>
struct Poi {
    Type x, y;
    Poi()=default;
    explicit Poi(Type x, Type y): x(x), y(y) {}

    Poi operator+(const Poi &p) const { return Poi(x+p.x, y+p.y); }
    Poi operator-(const Poi &p) const { return Poi(x-p.x, y-p.y); }
    Poi operator*(Type k) const { return Poi(x*k, y*k); }
    friend Poi operator*(Type k, const Poi &p) { return Poi(p.x*k, p.y*k); }

    Type operator*(const Poi &p) const { return x*p.x+y*p.y; }
    Type operator/(const Poi &p) const { return x*p.y-y*p.x; }

    bool operator==(const Poi &p) const { return x==p.x && y==p.y; }
    bool operator<(const Poi &p) const { return cmp_angle(*this, p)<0; }
    bool operator>(const Poi &p) const { return cmp_angle(*this, p)>0; }

    Poi reflect() const { return Poi(x, -y); }

    static Poi norm(const Poi &p) {
        Type g=gcd(abs(p.x), abs(p.y));
        return Poi(p.x/g, p.y/g);
    }
    static Poi angle(const Poi &from, const Poi &to) {
        return norm(Poi(from*to, to/from));
    }
    static int quadrant(const Poi &p) {
        if (p.x>=0) return p.y>=0? 1: 4;
        return p.y>=0? 2: 3;
    }

    static int cmp_angle(const Poi &a, const Poi &b) {
        int qa=quadrant(a), qb=quadrant(b);
        if (qa!=qb) return qa<qb? -1:1;

        Lint cr=Lint(a.x)*b.y-Lint(a.y)*b.x;
        if (cr==0) return 0;
        return cr>0? -1: 1;
    }
    static bool left_of(const Poi &a, const Poi &b) {
        return Lint(a.x)*b.y-Lint(a.y)*b.x>0;
    }
    static Poi min(const Poi &a, const Poi &b) { return a<b? a:b; }
    static Poi max(const Poi &a, const Poi &b) { return b<a? a:b; }

    static void sort(array<Poi, 2> &a) { if (left_of(a[1], a[0])) swap(a[0], a[1]); }
};

using Point=Poi<lint>;

pair<Point, Point> state(Point a, Point b) {
    if (b<a) swap(a, b);
    return {a, b};
}

array<Point, 2> remove_overlap(array<Point, 2> a, Point &s, Point &e) {
    Point::sort(a);
    array b={
        Point::min(a[0], a[0].reflect()),
        Point::min(a[1], a[1].reflect())
    };
    Point::sort(b);

    if (Point::left_of(a[0], Point(1, 0)) && Point::left_of(Point(1, 0), a[1]))
        s=Point::max(s, b[0]);
    else if (Point::left_of(a[0], Point(-1, 0)) && Point::left_of(Point(-1, 0), a[1]))
        e=Point::min(e, b[1]);
    return b;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(9);

    int T;
    cin >> T;
    for (int t=1; t<=T; t++) {
        int n;
        cin >> n;
        vector<array<Point, 2>> seg;
        Point s(1, 0), e(-1, 0);
        for (int i=0; i<n; i++) {
            int x, y, px, py;
            cin >> x >> y >> px >> py;
            Point dir(px-x, py-y);
            array<Point, 2> cur={
                Point::angle(dir, Point(-x, -y)),
                Point::angle(dir, Point(-x, 1000-y))
            };
            seg.emplace_back(remove_overlap(cur, s, e));
        }
        vector<array<Point, 2>> v;
        for (auto cur: seg) {
            if (cur[0]<s) cur[0]=s;
            if (e<cur[1]) cur[1]=e;
            if (!(cur[0]<cur[1])) continue;
            v.emplace_back(cur);
        }
        ranges::sort(v);
        v.push_back({e, e});

        double gap=0;
        map<pair<Point, Point>, double> dp, ndp;
        dp[{s, s}]=1;
        for (auto [l, r]: v) {
            ndp.clear();
            for (auto [cur, p]: dp) {
                auto [x, y]=cur;
                if (x<l) {
                    gap+=p;
                    continue;
                }
                if (p<eps) continue;
                ndp[state(Point::max(x, r), y)]+=p/2;
                ndp[state(x, Point::max(y, r))]+=p/2;
            }
            dp.swap(ndp);
            if (dp.empty()) break;
        }
        cout << "Case #" << t << ": " << gap << '\n';
    }
}