#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    transform(v.begin(), v.end(),
        ostream_iterator<string>(cout, "\n"),
        [](int k) {
            return string(k, '*');
        }
    );
}