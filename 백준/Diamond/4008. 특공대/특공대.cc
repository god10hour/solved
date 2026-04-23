#include <bits/stdc++.h>
#define int int64_t
using namespace std;

struct Line {
    int a, b;
    int fx(int x) {
        return a*x+b;
    }
    long double cross(Line k) {
        return static_cast<long double>(b-k.b)/(k.a-a);
    }
};

struct Vec {
    deque<Line> lines;
    void add(int a, int b) {
        Line f={a, b};
        while (lines.size()>1 && f.cross(lines.back())<=lines.back().cross(lines[lines.size()-2]))
            lines.pop_back();
        lines.push_back(f);
    }
    int query(int k) {
        while (lines.size()>1 && lines[0].fx(k)<=lines[1].fx(k))
            lines.pop_front();
        return lines[0].fx(k);
    }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    int a, b, c;
    cin >> n >> a >> b >> c;
    vector<int> v(n+1), s(n+1);
    for (int i=1; i<=n; i++) {
        cin >> v[i];
        s[i]=s[i-1]+v[i];
    }
    Vec dp;
    dp.add(b, 0);
    for (int i=1; i<=n; i++) {
        k=dp.query(s[i])+a*s[i]*s[i]+c;
        dp.add(-2*a*s[i]+b, k+a*s[i]*s[i]-b*s[i]);
    }
    cout << k;
}