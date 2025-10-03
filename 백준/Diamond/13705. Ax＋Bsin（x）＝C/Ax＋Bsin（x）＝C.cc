#include <bits/stdc++.h>
#define int __int128
#define float __float128
using namespace std;
float PI=3.1415926535897932384626Q;

float sine(float x) {
    x-=int(x/PI)*PI;
    float r=x, y=x, f=-x*x;
    for (float d=2; d<30; d+=2)
        r+=y*=f/(d*(d+1));
    return r;
}

int32_t main() {
    PI*=2;
    float A, B, C, l, r, x;
    long double a, b, c;
    cin >> a >> b >> c;
    A=a, B=b, C=c;
    float u=1000000, d=0.5;
    l=(C-B)/A, r=(C+B)/A;
    int t=100;
    while (t--) {
        x=(l+r)/2;
        float v=A*x+B*sine(x);
        if (v<C) l=x;
        else r=x;
    }
    cout << setprecision(6) << fixed << (long double)(int(u*r+d)/u);
}