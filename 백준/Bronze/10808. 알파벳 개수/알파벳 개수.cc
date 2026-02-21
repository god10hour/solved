#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    array<int, 26> a={};
    string s;
    cin >> s;
    for (auto c: s) a[c-97]++;
    for (auto i: a) cout << i << ' ';
}