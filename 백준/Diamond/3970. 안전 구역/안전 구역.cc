#include <bits/stdc++.h>
using namespace std;
const double PI=acos(-1.0);
const double TAU=PI*2;
const double EPS=1e-9;

struct Circle {
    double x, y, r;
    Circle() {}
    Circle(double x, double y, double r): x(x), y(y), r(r) {}

    double dot(const Circle &o) const {
        return x*o.x+y*o.y;
    }
    double norm() const {
        return hypot(x, y);
    }
};

double perimeter(vector<Circle> &c) {
    vector<bool> use(c.size(), 1);
    for (int i=0; i<c.size(); i++) {
        if (!use[i]) continue;
        for (int j=0; j<c.size(); j++) {
            if (i==j || !use[j]) continue;
            Circle d=Circle(c[i].x-c[j].x, c[i].y-c[j].y, 0);
            if (d.norm()+c[i].r<=c[j].r+EPS) {
                use[i]=0;
                break;
            }
        }
    }
    vector<Circle> v;
    for (int i=0; i<c.size(); i++)
        if (use[i])
            v.push_back(c[i]);
    if (v.empty()) return 0.0;
    if (v.size()==1) return TAU*v[0].r;
    int n=v.size();

    auto angle=[&](double th) {
        th=fmod(th, TAU);
        if (th<0) th+=TAU;
        return th;
    };

    vector<double> ev;
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            Circle d(v[i].x-v[j].x, v[i].y-v[j].y, 0);
            double D=d.norm(), dr=v[j].r-v[i].r;
            if (D<EPS) continue;
            double q=dr/D;
            if (q<-1.0-1e-12 || q>1.0+1e-12)
                continue;
            q=max(-1.0, min(1.0, q));
            double alpha=atan2(d.y, d.x);
            double beta=acos(q);
            ev.push_back(angle(alpha-beta));
            ev.push_back(angle(alpha+beta));
        }
    }
    if (ev.empty()) {
        int k=max_element(
                  v.begin(), v.end(),
                  [](const Circle &A, const Circle &B) {
                      return A.r<B.r;
                  }
              )-v.begin();
        return TAU*v[k].r;
    }
    sort(ev.begin(), ev.end());
    vector<double> events;
    for (double th: ev) {
        if (events.empty() || fabs(th-events.back())>EPS)
            events.push_back(th);
    }
    events.push_back(events.front()+TAU);

    auto support=[&](int i, double th)->double {
        Circle u(cos(th), sin(th), 0);
        return v[i].dot(u)+v[i].r;
    };
    auto active=[&](double th)->int {
        double max=-DBL_MAX;
        int idx=-1;
        for (int i=0; i<n; i++) {
            double x=support(i, th);
            if (x>max+EPS) {
                max=x;
                idx=i;
            }
        }
        return idx;
    };

    double arc=0.0, seg=0.0;
    for (size_t k=0; k<events.size()-1; k++) {
        double a=events[k], b=events[k+1];
        double mid=(a+b)*0.5;
        arc+=v[active(mid)].r*(b-a);
        int l=active(a-EPS);
        int r=active(a+EPS);
        if (l!=r) {
            Circle vec(-sin(a), cos(a), 0);
            Circle d(v[r].x-v[l].x, v[r].y-v[l].y, 0);
            double s=fabs(d.dot(vec));
            if (s>EPS) seg+=s;
        }
    }
    return arc+seg;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<Circle> v(n);
        for (int i=0; i<n; i++)
            cin >> v[i].x >> v[i].y >> v[i].r;
        cout << perimeter(v) << '\n';
    }
}