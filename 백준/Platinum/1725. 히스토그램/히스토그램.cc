#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, s=0;
    stack<int> p;
    cin >> n;
    vector<int> v(n);
    for (int i=0; i<n; i++)
        cin >> v[i];
    for (int i=0; i<n; i++) {
        while (!p.empty() && v[p.top()]>v[i]) {
            int h=v[p.top()];
            p.pop();
            s=max(s, h*(p.empty()?i:i-p.top()-1));
        }
        p.push(i);
    }
    while (!p.empty()) {
        int h=v[p.top()];
        p.pop();
        s=max(s, h*(p.empty()?n:n-p.top()-1));
    }
    cout << s << '\n';
}