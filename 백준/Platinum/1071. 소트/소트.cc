#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i=0; i<n; i++) cin >> v[i];
    vector<int> r;
    for (int i=0; i<n; i++) {
        sort(v.begin(), v.end());
        set s(v.begin(), v.end());
        if (s.size()!=2)
            if (r.empty() || r.back()+1!=v[0]) {
                r.push_back(v[0]);
                v.erase(v.begin());
            }
            else {
                r.push_back(*next(s.begin()));
                v.erase(find(v.begin(), v.end(), *next(s.begin())));
            }
        else if ((*s.begin())+1==*s.rbegin()||(r.size()&&r.back()+1==*(s.begin()))) {
                r.push_back(v.back());
                v.erase(v.end()-1);
            }
        else {
            r.push_back(v[0]);
            v.erase(v.begin());
        }
    }
    for (int k: r) cout << k << ' ';
}