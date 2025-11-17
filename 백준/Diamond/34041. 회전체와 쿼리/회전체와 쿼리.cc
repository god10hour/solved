#include <bits/stdc++.h>
using namespace std;
using ldb=long double;
constexpr ldb TAU=2.0L*acos(-1.0L);

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

    static Type dis(const Poi &a, const Poi &b) {
        Type dx=a.x-b.x, dy=a.y-b.y;
        return dx*dx + dy*dy;
    }
    static int ccw(const Poi &a, const Poi &b, const Poi &c) {
        Type d=a.x*b.y + b.x*c.y + c.x*a.y - a.x*c.y - b.x*a.y - c.x*b.y;
        return (d>0)-(d<0);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(10);
    int n, q;
    cin >> n;
    vector<Poi<ldb>> P(n);
    for (int i=0; i<n; i++)
        cin >> P[i].x >> P[i].y;
    int m=n*2;
    vector<Poi<ldb>> V(m);
    for (int i=0; i<m; i++) V[i]=P[i%n];

    vector<ldb> pc(m+1, 0), px(m+1, 0), py(m+1, 0);
    for (int i=0; i<m; i++) {
        ldb c=V[i]/V[i+1];
        ldb x=c*(V[i].x+V[i+1].x);
        ldb y=c*(V[i].y+V[i+1].y);
        pc[i+1]=pc[i]+c;
        px[i+1]=px[i]+x;
        py[i+1]=py[i]+y;
    }

    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (a>b) b+=n;
        ldb c=V[b]/V[a];

        ldb S0=pc[b]-pc[a]+c;
        ldb Sx=px[b]-px[a]+c*(V[a].x+V[b].x);
        ldb Sy=py[b]-py[a]+c*(V[a].y+V[b].y);

        ldb dx=V[b].x-V[a].x;
        ldb dy=V[b].y-V[a].y;
        ldb L=hypot(dx, dy);
        if (L==0) {
            cout << 0 << '\n';
            continue;
        }
        ldb cprime=dy*V[a].x-dx*V[a].y;

        auto volume=[&](ldb s0, ldb x, ldb y)-> ldb {
            ldb A=s0*0.5L;
            ldb Fx=x/6.0L;
            ldb Fy=y/6.0L;
            ldb S1=-dy*Fx+dx*Fy+cprime*A;
            return TAU*fabsl(S1)/L;
        };

        ldb V1=volume(S0, Sx, Sy);
        ldb V2=volume(pc[n]-S0, px[n]-Sx, py[n]-Sy);

        cout << min(V1, V2) << '\n';
    }
}