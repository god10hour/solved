#include <bits/stdc++.h>
using namespace std;
constexpr double EPS=1e-12;

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
    static Type ccw(const Poi &a, const Poi &b, const Poi &c) {
        Type d=a.x*b.y + b.x*c.y + c.x*a.y - a.x*c.y - b.x*a.y - c.x*b.y;
        return d;
    }
};
using Point=Poi<double>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> m >> n;
    vector<double> a(n+1), b(n+1);
    vector<Point> pts;
    pts.emplace_back(0.0, 0.0);
    int s=0;
    for (int i=1; i<=n; i++) cin >> a[i] >> b[i];
    for (int i=1; i<=n; i++) {
        if (fabs(a[i]+m)>EPS && fabs(a[i]-m)>EPS) pts.emplace_back(a[i], i);
        if (fabs(b[i]+m)>EPS && fabs(b[i]-m)>EPS) pts.emplace_back(b[i], i);
    }
    pts.emplace_back(0.0, n+1);
    int k=pts.size()-1;
    vector<int> ord(k+1), rid(k+1);
    vector<Point> p(k+1);
    iota(ord.begin(), ord.end(), 0);
    ranges::sort(ord, [&](int i, int j) {
        if (pts[i].y!=pts[j].y)
            return pts[i].y<pts[j].y;
        return pts[i].x<pts[j].x;
    });
    for (int i=0; i<ord.size(); i++) rid[ord[i]]=i;
    for (int i=0; i<ord.size(); i++) p[i]=pts[ord[i]];
    s=rid[s], k=rid[k];

    auto visible=[&](int i, int j)->bool {
        const Point &u=p[i], &v=p[j];
        if (!(u.y+EPS<v.y)) return false;
        auto inside=[&](double x)->bool {
            return x>-m+EPS && x<m-EPS;
        };
        if (i!=s && i!=k && !inside(u.x)) return false;
        if (j!=s && j!=k && !inside(v.x)) return false;
        double dy=v.y-u.y, dx=v.x-u.x;
        int yu=llround(u.y), yv=llround(v.y);
        for (int l=yu+1; l<=yv-1; l++) {
            if (l<1 || l>n) continue;
            double r=(l-u.y)/dy, xk=u.x+dx*r;
            if (xk<a[l]-1e-11 || xk>b[l]+1e-11) return false;
            if (!inside(xk)) return false;
        }
        return true;
    };
    vector dp(p.size(), 1e60);
    dp[s]=0.0;
    for (int i=0; i<p.size(); i++) {
        if (dp[i]>=1e59) continue;
        for (int j=i+1; j<p.size(); j++) {
            if (!visible(i, j)) continue;
            double w=sqrt(Point::dis(p[i], p[j]));
            dp[j]=min(dp[j], dp[i]+w);
        }
    }
    cout << fixed << setprecision(10) << dp[k] << '\n';
}
