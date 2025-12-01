#include <bits/stdc++.h>
using namespace std;
using lint=uint64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, r=0;
    cin >> n;
    vector<lint> v(n);
    for (lint &x: v) cin >> x;
    vector<lint> g, P;
    bitset<40000> sieve;
    set<lint> div;
    sieve.set();
    sieve[0]=sieve[1]=0;
    for (lint i=2; i<40000; i++) if (sieve[i]) {
        P.push_back(i);
        for (lint j=i*i; j<40000; j+=i) sieve[j]=0;
    }

    for (lint x: v) {
        for (lint &p: P) {
            if (x%p==0) {
                div.insert(p);
                while (x%p==0) x/=p;
            }
            if (x<p) break;
        }
        g.push_back(x);
        div.insert(x);
    }
    for (int i=0; i<g.size(); i++)
        for (int j=i+1; j<g.size(); j++)
            div.insert(gcd<lint>(g[i], g[j]));
    for (auto &d: div) if (d!=1) {
        int k=0;
        for (lint &x: v) if (x%d==0) k++;
        r=max(r, k);
    }
    cout << r << '\n';
}