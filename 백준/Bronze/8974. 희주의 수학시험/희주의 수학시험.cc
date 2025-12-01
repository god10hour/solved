#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<int> v, u;
    for (int i=0; i<47; i++)
        for (int j=0; j<i; j++)
            v.push_back(i);
    u.push_back(0);
    for (int i=0; i<v.size(); i++)
        u.push_back(u.back()+v[i]);

    int a, b;
    cin >> a >> b;
    cout << u[b]-u[a-1];
}