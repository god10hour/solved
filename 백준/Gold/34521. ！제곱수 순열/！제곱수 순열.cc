#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> v[4];
        for (int x=1; x<=n; x++)
            v[x&3].push_back(x);
        int ext=-1;
        if (v[2].size()==v[0].size()+1) {
            ext=v[2].back();
            v[2].pop_back();
        }
        vector<int> r;
        if (ext!=-1) {
            if (!v[1].empty()) {
                r.push_back(v[1][0]);
                r.push_back(ext);
                for (int i=1; i<v[1].size(); i++)
                    r.push_back(v[1][i]);
            }
            else r.push_back(ext);
        }
        else
            for (int x: v[1])
                r.push_back(x);
        for (int i=0; i<v[2].size(); i++) {
            r.push_back(v[2][i]);
            r.push_back(v[0][i]);
        }
        for (int x: v[3])
            r.push_back(x);
        for (int i=0; i<r.size(); i++)
            cout << r[i] << ' ';
        cout << '\n';
    }
}