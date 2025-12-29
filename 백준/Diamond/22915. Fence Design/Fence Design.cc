#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

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
    static int ccw(const Poi &a, const Poi &b, const Poi &c) {
        Type d=a.x*b.y + b.x*c.y + c.x*a.y - a.x*c.y - b.x*a.y - c.x*b.y;
        return (d>0)-(d<0);
    }

    static void sort_angle(vector<Poi> &v) {
        ranges::sort(
            v, [&](auto a, auto b) {
                Poi o(0, 0);
                if (a>o^b>o) return a>b;
                Type c=a/b;
                if (c) return c>0;
                return a*a<b*b;
            }
        );
    }
};

static int ccw_idx(const vector<Poi<lint>> &pts, int a, int b, int c) {
    return Poi<lint>::ccw(pts[a], pts[b], pts[c]);
}
static bool same_side(
        const vector<Poi<lint>> &pts,
        const array<array<int, 2>, 2> &f
    ) {
    int s1=ccw_idx(pts, f[0][0], f[1][0], f[1][1]);
    int s2=ccw_idx(pts, f[0][1], f[1][0], f[1][1]);
    return s1==0 || s2==0 || s1==s2;
}
static vector<int> rotate(const vector<int> &hull, const pair<int, int> &split) {
    int n=hull.size();
    auto in_split=[&](int v) {
        return v==split.first || v==split.second;
    };
    for (int i=0; i<n; i++) {
        int prev=(i-1+n)%n;
        if (in_split(hull[i]) && in_split(hull[prev])) {
            vector<int> r;
            r.reserve(n);
            for (int k=i; k<n; k++) r.push_back(hull[k]);
            for (int k=0; k<i; k++) r.push_back(hull[k]);
            return r;
        }
    }
    return hull;
}

inline void result(set<pair<int, int>> &r, int a, int b) {
    if (a>b) swap(a, b);
    r.insert({a, b});
}

void triangle(
        const vector<Poi<lint>> &pts,
        const vector<int> &left,
        const vector<int> &right,
        set<pair<int, int>> &r,
        unordered_set<int> &lookup
    ) {
    int p=0, q=1;
    int nl=left.size(), nr=right.size();
    while (1) {
        int p1=(p+1)%nl, q1=(q+1)%nr;
        if (ccw_idx(pts, left[p1], left[p], right[q])==+1) {
            result(r, left[p1], right[q]);
            lookup.insert(left[p]);
            p=p1;
            continue;
        }
        if (ccw_idx(pts, left[p], right[q], right[q1])==+1) {
            result(r, right[q1], left[p]);
            lookup.insert(right[q]);
            q=q1;
            continue;
        }
        break;
    }
}

vector<int> conquer(
        const vector<Poi<lint>> &pts,
        const vector<int> &left,
        const vector<int> &right,
        const pair<int, int> &split,
        set<pair<int, int>> &r
    ) {
    if (left.size()==2) return right;
    if (right.size()==2) return left;
    unordered_set<int> lookup;
    lookup.reserve(left.size()+right.size());

    vector<int> left_ccw=rotate(left, split), right_cw=right;
    ranges::reverse(right_cw);
    right_cw=rotate(right_cw, split);
    triangle(pts, left_ccw, right_cw, r, lookup);

    vector<int> right_ccw=rotate(right, split), left_cw=left;
    ranges::reverse(left_cw);
    left_cw=rotate(left_cw, split);
    triangle(pts, right_ccw, left_cw, r, lookup);

    vector<int> merged;
    merged.reserve(left.size()+right.size());
    for (int x: left_ccw) if (!lookup.contains(x)) merged.push_back(x);
    for (int i=1; i+1<right_ccw.size(); i++)
        if (int x=right_ccw[i]; !lookup.contains(x))
            merged.push_back(x);
    return merged;
}

vector<int> divide(
        const vector<Poi<lint>> &pts,
        vector<pair<int, int>> f,
        vector<int> cur,
        const pair<int, int> &split,
        bool has,
        set<pair<int, int>> &r,
        mt19937 &rng
    ) {
    if (cur.size()==2) return cur;
    if (cur.size()==3) {
        int p=-1;
        auto [a, b]=split;
        for (int v: cur)
            if (!(has && (v==a || v==b))) {
                p=v;
                break;
            }
        result(r, p, a);
        result(r, p, b);
        if (ccw_idx(pts, p, a, b)!=+1) swap(a, b);
        return {p, a, b};
    }

    pair<int, int> new_split;
    if (!f.empty()) {
        new_split=f.back();
        f.pop_back();
    }
    else {
        uniform_int_distribution<> dist(0, cur.size()-1);
        while (true) {
            int i=dist(rng), p=cur[i];
            swap(cur[i], cur.back());
            uniform_int_distribution<> dist2(0, cur.size()-2);
            int q=cur[dist2(rng)];
            if (p>q) swap(p, q);
            if (!r.contains({p, q})) {
                new_split={p, q};
                break;
            }
        }
    }
    result(r, new_split.first, new_split.second);

    vector<int> left, right;
    left.reserve(cur.size());
    right.reserve(cur.size());
    pair rem={-1, -1};
    bool z=!f.empty();
    if (z) rem=f.back();
    array<bool, 4> have={};
    for (int x: cur) {
        int s=ccw_idx(pts, new_split.first, new_split.second, x);
        if (s!=+1) {
            left.push_back(x);
            if (z) {
                if (x==rem.first) have[0]=1;
                if (x==rem.second) have[1]=1;
            }
        }
        if (s!=-1) {
            right.push_back(x);
            if (z) {
                if (x==rem.first) have[2]=1;
                if (x==rem.second) have[3]=1;
            }
        }
    }

    vector<pair<int, int>> lf, rf;
    if (z && have[0] && have[1]) lf=f;
    if (z && have[2] && have[3]) rf=f;
    auto lhull=divide(pts, lf,  left,  new_split, true, r, rng);
    auto rhull=divide(pts, rf, right, new_split, true, r, rng);
    return conquer(pts, lhull, rhull, new_split, r);
}

string fence(mt19937 &rng) {
    int n;
    cin >> n;
    vector<Poi<lint>> pts(n);
    array<array<int, 2>, 2> f;
    for (int i=0; i<n; i++) cin >> pts[i].x >> pts[i].y;
    for (int i=0; i<2; i++) {
        int a, b;
        cin >> a >> b;
        if (a>b) swap(a, b);
        f[i]={a-1, b-1};
    }
    if (!same_side(pts, f)) swap(f[0], f[1]);
    vector<pair<int, int>> g(2);
    for (int i=0; i<2; i++) g[i]={f[i][0], f[i][1]};
    set<pair<int, int>> r;
    vector<int> cur(n);
    iota(cur.begin(), cur.end(), 0);
    auto hull=divide(pts, g, cur, {0, 0}, false, r, rng);

    set given={g[0], g[1]};
    vector<pair<int, int>> out;
    out.reserve(r.size());
    for (auto &e: r) if (!given.contains(e)) out.push_back(e);

    ostringstream oss;
    oss << r.size()-2 << '\n';
    for (int i=0; i<out.size(); i++) {
        oss << out[i].first+1 << ' ' << out[i].second+1 << '\n';
    }
    return oss.str();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    mt19937 rng(998244353);
    int t;
    cin >> t;
    for (int i=0; i<t; i++)
        cout << "Case #" << i+1 << ": " << fence(rng);
}