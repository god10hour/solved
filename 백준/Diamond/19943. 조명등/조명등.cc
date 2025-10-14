#include <bits/stdc++.h>
#define int int64_t
using namespace std;

struct Poi {
    int x, y;
    Poi(int x=0, int y=0): x(x), y(y) {}
    bool operator<=(const Poi &p) const {
        return 1.0*x/y<=1.0*p.x/p.y;
    }
};

struct Convex {
private:
    static int F(const Poi &p, int x) {
        return p.x*x+p.y;
    }
    static Poi C(const Poi &a, const Poi &b) {
        return {a.y-b.y, b.x-a.x};
    }
    deque<Poi> s;
public:
    void insert(int a, int b) {
        while (s.size()>1 && C(s.back(), Poi(a, b))<=C(s[s.size()-2], s.back()))
            s.pop_back();
        s.push_back(Poi(a, b));
    }
    int query(int x) {
        while (s.size()>1 && F(s[0], x)>=F(s[1], x))
            s.pop_front();
        return F(s[0], x);
    }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pair<int, int>> v;
        while (n--) {
            int a, b;
            cin >> a >> b;
            while (!v.empty() && v.back().second-v.back().first<=b-a)
                v.pop_back();
            if (v.empty() || v.back().first+v.back().second<a+b)
                v.push_back({a, b});
        }
        Convex CHT;
        int dp=0;
        for (const auto &[x, h]: v) {
            CHT.insert(-2*(x-h), dp+(x-h)*(x-h));
            dp=CHT.query(x+h)+(x+h)*(x+h);
        }
        cout << dp/4 << '.';
        cout << setw(2) << setfill('0') << dp%4*25 << '\n';
    }
}