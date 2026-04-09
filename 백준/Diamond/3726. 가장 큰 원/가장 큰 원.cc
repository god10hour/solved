#include <bits/stdc++.h>
using namespace std;
using rea=double;
constexpr rea eps=1e-12;

struct Seg {
    rea ax, ay, bx, by;
};

bool forbid(const Seg &s, rea r, rea &left, rea &right) {
    auto [ax, ay, bx, by]=s;
    rea dx=bx-ax, dy=by-ay, r_2=r*r;
    array<pair<rea, rea>, 3> segs;
    int cnt=0;
    auto add=[&](rea l, rea rr) {
        if (l+eps<rr) segs[cnt++]={l, rr};
    };

    if (fabs(dx)<eps) {
        rea lo=min(ay, by), hi=max(ay, by);
        rea d=0;
        if (lo>0) d=lo;
        if (hi<0) d=-hi;
        if (d>=r-eps) return false;
        rea w=sqrt(max(rea(0), r_2-d*d));
        left=ax-w, right=ax+w;
        return true;
    }

    rea x0=ax+ay*dy/dx;
    rea x1=bx+by*dy/dx;
    if (x0>x1) swap(x0, x1);

    if (r_2>ay*ay+eps) {
        rea w=sqrt(r_2-ay*ay);
        rea ll=ax-w, rr=ax+w;
        if (dx>0)
            rr=min(rr, x0);
        else ll=max(ll, x0);
        add(ll, rr);
    }

    if (r_2>by*by+eps) {
        rea w=sqrt(r_2-by*by);
        rea ll=bx-w, rr=bx+w;
        if (dx>0)
            ll=max(ll, x1);
        else rr=min(rr, x1);
        add(ll, rr);
    }

    if (fabs(dy)<eps) {
        if (fabs(ay)<r-eps) add(min(ax, bx), max(ax, bx));
    }
    else {
        rea c=dx*ay-dy*ax, k=r*sqrt(dx*dx+dy*dy);
        rea ll=(-k-c)/dy, rr=(k-c)/dy;
        if (ll>rr) swap(ll, rr);
        ll=max(ll, x0);
        rr=min(rr, x1);
        add(ll, rr);
    }
    if (!cnt) return false;

    sort(segs.begin(), segs.begin()+cnt);
    left=segs[0].first, right=segs[0].second;
    for (int i=1; i<cnt; i++) {
        if (segs[i].first<=right+eps)
            right=max(right, segs[i].second);
        else break;
    }
    return true;
}

bool feasible(const vector<Seg> &a, rea L, rea r) {
    vector<pair<rea, rea>> ban;
    ban.reserve(a.size());

    for (auto &s: a) {
        rea left, right;
        if (forbid(s, r, left, right))
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
        for (int i=0; i<48; i++) {
            rea mid=(l+r)/2;
            (feasible(pts, L, mid)? l: r)=mid;
        }
        cout << l << '\n';
    }
}