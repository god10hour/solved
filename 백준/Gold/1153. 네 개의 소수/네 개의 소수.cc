#include <bits/stdc++.h>
using namespace std;
const int MAX=1000001;

int main() {
    vector<bool> sieve(MAX, 1);
    vector<int> p;
    sieve[0]=sieve[1]=0;
    for (int i=2; i<MAX; i++)
        if (sieve[i]) {
            p.push_back(i);
            for (int j=i*2; j<MAX; j+=i)
                sieve[j]=0;
        }

    int n;
    cin >> n;
    if (n<8) return !(cout << -1);
    if (n%2)
        cout << "2 3 ", n-=5;
    else cout << "2 2 ", n-=4;
    for (int i=0; i<p.size(); i++)
        if (sieve[n-p[i]])
            return !(cout << p[i] << ' ' << n-p[i]);
}