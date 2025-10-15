#include <bits/stdc++.h>
using namespace std;
string r[4]={
    "A+=A",
    "B+=B",
    "A+=B",
    "B+=A"
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<int> v;
    int64_t a, b;
    cin >> a >> b;
    while (a!=b)
        if (b%2==0) b/=2, v.push_back(0);
        else if (a%2==0) a/=2, v.push_back(1);
        else if (a>b) a+=b, v.push_back(2);
        else b+=a, v.push_back(3);
    cout << v.size() << '\n';
    for (int i: v) cout << r[i] << '\n';
}