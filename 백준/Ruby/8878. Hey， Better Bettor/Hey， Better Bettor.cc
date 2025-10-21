#include <bits/stdc++.h>
using namespace std;
const int N=21000;
long double power[N*2];

long double pred(long double x, int a, int b) {
    return (b*(power[a]-1)-a*x*power[a]*(power[b]-1))/(power[a+b]-1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    long double x, p, r=0;
    cin >> x >> p;
    if (p<1e-6) return !(cout << 0);
    x=1.0-x/100.0;
    p=(100.0-p)/p;
    power[0]=1;
    for (int i=1; i<N*2; i++) power[i]=p*power[i-1];

    int a=1, b=1;
    while (a<N) {
        long double z=pred(x, a, b);
        r=max(r, z);
        while (b<N) {
            long double y=pred(x, a, b+1);
            if (y<z) break;
            r=max(r, y);
            b++, z=y;
        }
        a++;
    }
    cout << fixed << setprecision(9) << r;
}