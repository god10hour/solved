#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

lint floor_div(lint a, lint b) {
    lint q=a/b, r=a%b;
    if (r && a<0^b<0) q--;
    return q;
}
lint ceil_div(lint a, lint b) { return -floor_div(-a, b); }

bool possible(lint k, const vector<lint> &p) {
    int n=p.size(), L=n-1;
    lint l=0, r=k;

    for (int i=0; i<n; i++) {
        lint num=p[i]-k*(L-i), den=i*2-L;
        if (den==0 && num>0) return false;
        if (den>0) l=max(l, ceil_div(num, den));
        if (den<0) r=min(r, floor_div(num, den));
    }
    if (l!=r+1) return l<r+1;

    lint a=r, b=k-1-a;
    if (a<0 || b<0) return false;
    vector<int> diff(n+1);
    for (int i=0; i<n; i++) {
        lint cur=a*i+b*(L-i), u=p[i]-cur;
        if (u<1) continue;
        lint s=max<lint>(0, i-u+1);
        lint e=min<lint>(L, i+u-1);
        diff[s]++, diff[e+1]--;
    }

    int cover=0;
    for (int i=0; i<n; i++) {
        cover+=diff[i];
        if (cover==0) return true;
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<lint> p(n);
        for (auto &x: p) cin >> x;

        lint l=0, r=ceil_div(1e18, n-1)*2;
        while (l<r) {
            lint mid=(l+r)/2;
            if (possible(mid, p))
                r=mid;
            else l=mid+1;
        }
        cout << r << '\n';
    }
}