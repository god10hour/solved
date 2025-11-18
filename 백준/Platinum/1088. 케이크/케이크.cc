#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(10);
    int n, m;
    double r=numeric_limits<double>::infinity();
    cin >> n;
    vector<int> a(n), b(n);
    vector<double> c(n);
    for (int i=0; i<n; i++) cin >> a[i];
    for (int i=0; i<n; i++) b[i]=1, c[i]=a[i];
    r=min(r, *ranges::max_element(c)-*ranges::min_element(c));

    cin >> m;
    while (m--) {
        int t=ranges::max_element(c)-c.begin();
        b[t]++, c[t]=1.0*a[t]/b[t];
        r=min(r, *ranges::max_element(c)-*ranges::min_element(c));
    }
    cout << r << '\n';
}