#include <bits/stdc++.h>
using namespace std;
using rea=long double;
constexpr rea PI=acosl(-1.0L);
constexpr rea EPS=1e-7;

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

    Poi rot90() const { return Poi(-y, x); }
    static Type dis(const Poi &a, const Poi &b) {
        Type dx=a.x-b.x, dy=a.y-b.y;
        return dx*dx + dy*dy;
    }
    static int ccw(const Poi &a, const Poi &b, const Poi &c) {
        Type d=a.x*b.y + b.x*c.y + c.x*a.y - a.x*c.y - b.x*a.y - c.x*b.y;
        return (d>0)-(d<0);
    }
};

bool run_one(
    const array<Poi<rea>, 4> &pts,
    const array<int, 4> &side,
    rea theta, rea &out
) {
    Poi u(cosl(theta), sinl(theta));
    Poi v(-sinl(theta), cosl(theta));
    array<rea, 4> x, y;
    array<int, 4> idx;
    for (int i=0; i<4; i++) {
        x[i]=u*pts[i];
        y[i]=v*pts[i];
    }
    for (int i=0; i<4; i++) idx[side[i]]=i;

    rea xmin=x[idx[0]]-5.0L;
    rea xmax=x[idx[1]]+5.0L;
    rea ymin=y[idx[2]]-5.0L;
    rea ymax=y[idx[3]]+5.0L;
    rea dx=xmax-xmin, dy=ymax-ymin, S=(dx+dy)*0.5L;
    if (fabsl(dx-dy)>EPS) return false;
    if (S<=10.L+EPS) return false;

    for (int i=0; i<4; i++) {
        rea X=x[i]-xmin, Y=y[i]-ymin;
        if (X<-EPS || X>S+EPS || Y<-EPS || Y>S+EPS) return false;

        switch (side[i]) {
        case 0:
            if (fabsl(X-5.0L)>EPS) return false;
            if (Y<=5.0L+EPS) return false;
            if (S-X<=5.0L+EPS) return false;
            if (S-Y<=5.0L+EPS) return false;
            break;
        case 1:
            if (fabsl(S-X-5.0L)>EPS) return false;
            if (X<=5.0L+EPS) return false;
            if (Y<=5.0L+EPS) return false;
            if (S-Y<=5.0L+EPS) return false;
            break;
        case 2:
            if (fabsl(Y-5.0L)>EPS) return false;
            if (X<=5.0L+EPS) return false;
            if (S-X<=5.0L+EPS) return false;
            if (S-Y<=5.0L+EPS) return false;
            break;
        default:
            if (fabsl(S-Y-5.0L)>EPS) return false;
            if (X<=5.0L+EPS) return false;
            if (Y<=5.0L+EPS) return false;
            if (S-X<=5.0L+EPS) return false;
        }
    }

    out=S;
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(2);
    int T;
    cin >> T;
    for (int t=1; t<=T; t++) {
        array<Poi<rea>, 4> pts;
        for (int i=0; i<4; i++) cin >> pts[i].x >> pts[i].y;
        rea rs=-1.0L;

        array side={0, 1, 2, 3};
        do {
            array idx={-1, -1, -1, -1};
            for (int i=0; i<4; i++) idx[side[i]]=i;
            Poi<rea> A=pts[idx[1]]-pts[idx[0]];
            Poi<rea> B=pts[idx[3]]-pts[idx[2]];
            rea C=A.x-B.y, D=A.y+B.x;

            if (fabsl(C)<EPS*EPS && fabsl(D)<EPS*EPS) {
                for (int i=0; i<60000; i++) {
                    rea theta=PI*2.0L*i/60000, S;
                    if (run_one(pts, side, theta, S))
                        if (S>rs) rs=S;
                }
            }
            else {
                rea theta0=atan2l(-C, D);
                for (int i=0; i<2; i++) {
                    rea theta=theta0+i*PI, S;
                    if (run_one(pts, side, theta, S))
                        if (S>rs) rs=S;
                }
            }
        } while (ranges::next_permutation(side).found);

        cout << "Case " << t << ": ";
        if (rs<0)
            cout << "no solution\n";
        else cout << rs << '\n';
    }
}