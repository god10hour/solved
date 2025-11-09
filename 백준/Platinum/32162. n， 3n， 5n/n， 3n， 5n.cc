#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;

int f(lint n, int p) {
    int c=0;
    while (n%p==0) {
        n/=p;
        if (++c==3) c=0;
    }
    return c;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<lint> A;
    A.reserve(100000);

    for (lint n=1; A.size()<100000; n++) {
        int a=f(n, 3);
        int b=f(n, 5);
        if (a==b) A.push_back(n);
    }

    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        cout << A[k-1] << '\n';
    }
}
