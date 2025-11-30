#include <bits/stdc++.h>
using namespace std;

struct BIT {
    int n;
    vector<int> t;
    BIT(int n=0) { init(n); }
    void init(int n_) {
        n=n_;
        t.assign(n+1, 0);
    }
    void add(int i, int v) {
        for (; i<=n; i+=i&-i) t[i]+=v;
    }
    int sum(int i) const {
        int r=0;
        for (; i>0; i-=i&-i) r+=t[i];
        return r;
    }
};

int n, q;
string s;
BIT tree;

inline bool atfish(int i) {
    auto get=[&](int k) {
        string r="";
        for (int j=k; j<k+3; j++) {
            char c=s[j];
            if (tree.sum(j)&1) c=c=='<'? '>': '<';
            r+=c;
        }
        return r;
    };
    string a=get(i);
    return a=="<><" || a=="><>";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> s >> q;
    s=" "+s;
    tree.init(n+2);

    int fish=0;
    if (n>=3) for (int i=1; i<=n-2; i++) {
        string a=s.substr(i, 3);
        if (atfish(i)) fish++;
    }

    while (q--) {
        int t;
        cin >> t;
        if (t==1) {
            int l, r;
            cin >> l >> r;
            if (n<3) {
                tree.add(l, 1);
                tree.add(r+1, -1);
                continue;
            }

            vector<int> olds,  cand={l-2, l-1, l, r-2, r-1, r};
            ranges::sort(cand);
            cand.erase(ranges::unique(cand).begin(), cand.end());
            olds.reserve(cand.size());

            for (int x: cand) {
                if (x<1 || x>n-2) {
                    olds.push_back(0);
                    continue;
                }
                olds.push_back(atfish(x));
            }

            tree.add(l, 1);
            if (r<n) tree.add(r+1, -1);
            int idx=0;
            for (int x: cand) {
                if (x<1 || x>n-2) {
                    idx++;
                    continue;
                }
                int now=atfish(x);
                fish+=now-olds[idx];
                idx++;
            }
        }
        else cout << fish << '\n';
    }
}
