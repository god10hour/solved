#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int b, n, m;
    cin >> b >> n >> m;
    unordered_map<string, int> menu;
    for (int i=0; i<n; i++) {
        string name;
        int p;
        cin >> name >> p;
        menu[name]=p;
    }
    for (int i=0; i<m; i++) {
        string name;
        cin >> name;
        b-=menu[name];
    }
    if (b<0) cout << "un";
    cout << "acceptable";
}
