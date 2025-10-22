#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    vector<int> dig(10, 0);
    cin >> s;
    for (char c: s)
        dig[(c-'0'+9)%10]++;
    int m=1001, r=0;
    for (int i=0; i<10; i++)
        if (dig[i]<m) m=dig[i], r=i;
    if (r==9) {
        cout << 1;
        cout << string(dig[9]+1, '0');
        return 0;
    }
    cout << string(dig[r]+1, '0'+r+1);
}
