#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int b, s=0;
        string d;
        cin >> b >> d;
        for (char c :d) s+=c-'0';
        cout << s%(b-1) << '\n';
    }
}