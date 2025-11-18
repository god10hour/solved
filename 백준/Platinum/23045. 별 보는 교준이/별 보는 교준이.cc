#include <bits/stdc++.h>
using namespace std;

template <typename Type>
struct Poi {
    Type x, y;
    Poi()=default;
    explicit Poi(Type x, Type y): x(x), y(y) {}

    Poi operator-() const { return Poi(-x, -y); }
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
    int n, s=0;
    cin >> n;
    vector<Poi<int>> v(n);
    for (int i=0; i<n; i++)
        cin >> v[i].x >> v[i].y;
    for (int i=0; i<n; i++) {
        vector<Poi<int>> slopes;
        for (int j=i+1; j<n; j++) {
            Poi d=v[i]-v[j];
            if (d.x<0) d=-d;
            int g=__gcd(d.x, d.y);
            d=Poi(d.x/g, d.y/g);
            slopes.push_back(d);
        }
        sort(slopes.begin(), slopes.end());
        s+=ranges::unique(slopes).begin()-slopes.begin();
    }
    cout << s*2 << '\n';
}