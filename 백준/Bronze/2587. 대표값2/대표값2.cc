#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int s=0;
    vector<int> v(5);
    for (int i=0; i<5; i++)
        cin >> v[i];
    sort(v.begin(), v.end());
    for (int i=0; i<5; i++)
        s+=v[i];
    cout << s/5 << '\n' << v[2];
}