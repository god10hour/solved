#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, a, b, c, d;
    cin >> n;
    a=(n+2)/3, b=(n+1)/2-1;
    c=(n-a+1)/2, d=(n-b+1)/2;
    int r=(a+b+2)*(b-a+1)/2;
    r-=(c+d)*(c-d+1);
    if ((n-a)%2) r+=c;
    if ((n-b)%2==0) r+=d;
    cout << r;
}