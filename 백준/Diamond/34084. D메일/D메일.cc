#include <bits/stdc++.h>
using namespace std;

int eval(int n, int x) {
    int v=0;
    for (int k=0; k*2+1<n; k++) {
        int a=x>>(k*2)&1;
        int b=x>>(k*2+1)&1;
        v^=a&b;
    }
    if (n&1) v^=x>>(n-1)&1;
    return v;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, T;
    cin >> n >> T;
    int M=1<<n;

    string s;
    s.reserve(M);
    for (int i=0; i<M; i++) s.push_back(char('0'+eval(n, i)));
    cout << s << endl;

    auto ask=[&](int &cur, int tar) ->int {
        int a=cur^tar;
        cout << "? " << a << endl;
        int bit;
        cin >> bit;
        cur=tar;
        return bit;
    };
    for (int t=0; t<T; t++) {
        int cur=0;
        int b0=ask(cur, 0);
        vector delta(n, 0);
        for (int i=0; i<n; i++)
            delta[i]=b0^ask(cur, 1<<i);

        int x=0;
        for (int k=0; k*2+1<n; k++) {
            x|=delta[k*2]  <<(k*2+1);
            x|=delta[k*2+1]<<(k*2);
        }

        if (n&1) {
            int q=0;
            for (int k=0; k*2+1<n; k++) {
                int a=x>>(k*2)&1;
                int b=x>>(k*2+1)&1;
                q^=a&b;
            }
            x|=(b0^q)<<(n-1);
        }
        cout << "! " << x << endl;
    }
}