#include <bits/stdc++.h>
using namespace std;
using rea=long double;
constexpr rea eps=1e-12L;

struct Seg {
    rea ax, ay, bx, by;
};
rea dist(const Seg &s, rea x) {
    rea vx=s.bx-s.ax, vy=s.by-s.ay;
    rea wx=x-s.ax,    wy=-s.ay;
    rea len=vx*vx + vy*vy;
    rea k=(wx*vx + wy*vy)/len;
    k=clamp<rea>(k, 0, 1);
    rea cx=s.ax+k*vx, cy=s.ay+k*vy;
    return hypotl(x-cx, cy);
}

rea argmin(const Seg &s) {
    rea dx=s.bx-s.ax;
    rea dy=s.by-s.ay;
    if (fabsl(dy)<eps) return (s.ax+s.bx)/2;
    if (s.ay*s.by<=0)  return s.ax+dx*-s.ay/dy;
    if (fabsl(s.ay)<fabsl(s.by)) return s.ax;
    return s.bx;
}

bool feasible(const vector<Seg> &a, rea L, rea r) {
    vector<pair<rea, rea>> ban;
    ban.reserve(a.size());

    for (auto &s : a) {
        rea x0=argmin(s);
        rea d0=dist(s, x0);
        if (d0>=r-eps) continue;

        rea lo=min(s.ax, s.bx)-r;
        rea hi=max(s.ax, s.bx)+r;

        rea ll=lo, rr=x0;
        for (int i=0; i<70; i++) {
            rea mid=(ll+rr)/2;
            (dist(s, mid)<r? rr: ll)=mid;
        }
        rea left=rr;

        ll=x0, rr=hi;
        for (int i=0; i<70; i++) {
            rea mid=(ll+rr)/2;
            (dist(s, mid)<r? ll: rr)=mid;
        }
        rea right=ll;
        ban.emplace_back(left, right);
    }

    ranges::sort(ban);
    rea cur=0;
    int i=0, n=ban.size();
    while (cur<=L) {
        rea opt=cur;
        while (i<n && ban[i].first<cur-eps)
            opt=max(opt, ban[i++].second);
        if (opt<=cur+eps) return true;
        cur=opt;
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(3);
    int t;
    cin >> t;
    while (t--) {
        int n, L;
        cin >> n >> L;
        vector<Seg> pts(n);
        for (auto &[ax, ay, bx, by]: pts) cin >> ax >> ay >> bx >> by;

        rea l=0, r=40000;
        for (int i=0; i<70; i++) {
            rea mid=(l+r)/2;
            (feasible(pts, L, mid)? l: r)=mid;
        }
        cout << l << '\n';
    }
}